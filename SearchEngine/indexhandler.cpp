#include "indexhandler.h"
#include "documentparser.h"
#include "indexinterface.h"
#include "wordref.h"
#include "avltree.h"
#include "rapidxml.hpp"
#include "rapidxml_print.hpp"
#include <string>
#include <sstream>
#include <iostream>
#include <fstream>
#include <cstdio>
#include <algorithm>

using namespace std;

IndexHandler::IndexHandler()
{
    indexType = 0;
    numWords = 0;
    numPages = 0;
    fileName = "PersistentIndex.txt";
}

vector<WordRef> IndexHandler::indexPaths(const vector<string>& paths)
{
    /// Maybe put stopwords into an array instead of reading them from file
    DocumentParser dp;

    // Create vector to store all of the WordRefs that are indexed
    vector<WordRef> refs;
    // Create vector to store the most recently indexed WordRefs
    vector<WordRef> newRefs;

    // Parse the xml file at each path
    // Get the new WordRefs that are indexed and add them to the vector of all new WordRefs
    for(size_t i=0; i<paths.size(); i++)
    {
        dp.parseFile(paths[i], index, newRefs);
        refs.insert(refs.end(), newRefs.begin(), newRefs.end());
    }

    // Add the number of new WordRefs to the total number of WordRefs
    numPages += refs.size();

    // Create a vector of string-int pairs where the string is the word
    // and the int is the corpus frequency for that word
    vector<pair<string,int>> pairs;

    // Create a pair for each WordRef and add them to a vector
    for(size_t m=0; m<refs.size(); m++)
    {
        string word = refs[m].getWord();
        int corpFreq = refs[m].getCorpusFreq();
        pair<string,int> token = make_pair(word, corpFreq);
        pairs.push_back(token);
    }

    // Sort the vector of string-int pairs based on the int value from greatest to least
    sort(pairs.begin(), pairs.end(), [](const pair<string,int> &left, const pair<string,int> &right) {
        return left.second > right.second;
    });

    // Copy the top 50 most frequent words to the top50Words vector
    copy(pairs.begin(), pairs.begin() + (pairs.size() > 50 ? 50 : pairs.size()), top50Words.begin());

    return refs;
}

void IndexHandler::setIndexType(int it)
{
    if(it >= 1 && it <= 2)
        indexType = it;
    else
        cerr << "Error: Cannot set indexType, invalid index type\n";
}

int IndexHandler::getIndexType()
{
    return indexType;
}

int IndexHandler::getNumWords()
{
    return numWords;
}

int IndexHandler::getNumPages()
{
    return numPages;
}

std::vector<std::pair<std::string,int>> IndexHandler::getTop50Words()
{
    return top50Words;
}

vector<string>& IndexHandler::getPaths()
{
    return filePaths;
}

vector<string>& IndexHandler::getNewPaths()
{
    return newPaths;
}

string IndexHandler::getFileName()
{
    return fileName;
}

void IndexHandler::addPath(string newPath)
{
    filePaths.push_back(newPath);
}

void IndexHandler::addNewPath(string newPath)
{
    newPaths.push_back(newPath);
}

void IndexHandler::clearIndex()
{
    filePaths.clear();
    newPaths.clear();
    numWords = 0;
    numPages = 0;
    remove(fileName.c_str());
}

void IndexHandler::createIndex()
{
    // Create the type of the index based on the index type
    if(indexType == 1)
        index = new AvlTree;
    else if(indexType == 2){
        ///index = new HashTableIndex;
        cout << "\nHash Table not yet implemented\n";}
    else
        cerr << "Error: Could not create index, invalid index type\n";
}

void IndexHandler::writePersistentIndex(const vector<WordRef>& wordRefs)
{
    // Open file for output
    persistentIndexFile.open(fileName, ios::out);

    // Verify that file was opened correctly
    if(!persistentIndexFile)
    {
        cerr << "Error: Output file \"" << fileName << "\" was not opened correctly\n";
        exit(EXIT_FAILURE);
    }

    // Create DOM tree
    rapidxml::xml_document<> doc;

    // Loop through each WordRef in vector
    for(size_t i=0; i<wordRefs.size(); i++)
    {
        rapidxml::xml_node<> *wordRef = doc.allocate_node(rapidxml::node_element, "wordRef");
        rapidxml::xml_attribute<> *word = doc.allocate_attribute("word", wordRefs[i].getWord().c_str());
        wordRef->append_attribute(word);

        // Get the vector of PageLocations for the current WordRef
        vector<PageLocation> refs = wordRefs[i].getRefs();

        // Loop through each PageLocation in the vector
        for(size_t j=0; j<refs.size(); j++)
        {
            rapidxml::xml_node<> *pair = doc.allocate_node(rapidxml::node_element, "pair");
            rapidxml::xml_attribute<> *id = doc.allocate_attribute("id", to_string(refs[j].getPageID()).c_str());
            pair->append_attribute(id);

            // Get the vector of indicies where the word is found in the text
            vector<int> wordIndices = refs[j].getWordIndices();

            // Create a space delineated string of the indices
            string indicesStr = "";
            for(size_t k=0; k<wordIndices.size(); k++)
            {
                indicesStr += wordIndices[k];
                indicesStr += " ";
            }
            rapidxml::xml_attribute<> *indices = doc.allocate_attribute("indices", indicesStr.c_str());
            pair->append_attribute(indices);
            wordRef->append_node(pair);
        }
    }

    // Write DOM tree to output file
    persistentIndexFile << doc;

    // Close input file
    persistentIndexFile.close();
}

void IndexHandler::readPersistentIndex()
{
    // Open file for imput
    persistentIndexFile.open(fileName, ios::in);

    // Verify that file was opened correctly
    if(!persistentIndexFile)
    {
        cerr << "Error: Input file \"" << fileName << "\" was not opened correctly\n";
        exit(EXIT_FAILURE);
    }

    string xmlFileString;

    persistentIndexFile.seekg(0, ios::end);
    xmlFileString.reserve(persistentIndexFile.tellg());
    persistentIndexFile.seekg(0, ios::beg);

    xmlFileString.assign((istreambuf_iterator<char>(persistentIndexFile)), istreambuf_iterator<char>());
    persistentIndexFile.close();

    // Create DOM tree
    rapidxml::xml_document<> doc;
    ///rapidxml::parse_non_destructive|rapidxml::parse_no_data_nodes
    doc.parse<rapidxml::parse_no_data_nodes>(&xmlFileString[0]);

    // Create the pointers to move around tree, pair has  dummy value
    rapidxml::xml_node<> *wordRef = doc.first_node("wordRef");
    rapidxml::xml_node<> *pair = doc.first_node("wordRef");
    rapidxml::xml_node<> *elem;


    while(wordRef != NULL)
    {
        WordRef wr;
        //extracts the necessary imformation from the xml wordRef
        elem = wordRef->first_node("word");
        string word = elem->value();
        // Set the word of WordRef
        wr.setWord(word);

        pair = elem->next_sibling("pair");

        while(pair != NULL)
        {
            elem = pair->first_node("id");
            string id = elem->value();
            elem = elem->next_sibling("indices");
            string indices = elem->value();
            pair = pair->next_sibling("pair");

            // Convert id to integer
            int idInt = stoi(id);

            // Create a stringstream from the string of indices
            stringstream indicesSS(indices);
            string indexStr;
            vector<int> indicesVect;

            // Read each integer index and add it to the vector
            while(indicesSS >> indexStr)
            {
                indicesVect.push_back(stoi(indexStr));
            }

            // Add the page location data to the WordRef
            wr.insertRef(idInt, indicesVect);

            // Clear vector for new indicies in next pair
            indicesVect.clear();
        }

        // Insert the WordRef into the index
        ///index.insert(wr);

        // Go to the next wordRef in the
        wordRef = wordRef->next_sibling("wordRef");

        //will need to add the document number and file path to another data structure for lookup
        //add possibly another one for user/editor name, etc..
        //readFromFileIndex();
    }
}
