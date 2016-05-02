#include "indexhandler.h"
#include "documentparser.h"
#include "indexinterface.h"
#include "wordref.h"
#include "avltree.h"
#include "rapidxml.hpp"
#include "myhash.h"
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
    fileName = "PersistentIndex.xml";
    dp.readStopWords("stopwords.txt");
    index = nullptr;
}

void IndexHandler::indexPaths(const vector<string>& paths)
{
    // Parse the xml file at each path
    for(size_t i=0; i<paths.size(); i++)
    {
        dp.parseFile(paths[i], index);
    }

    // Clear the vector of the new paths that were added to the index
    newPaths.clear();
}

void IndexHandler::setIndexType(int it)
{
    if(it >= 1 && it <= 2)
        indexType = it;
    else
        cerr << "Error: Cannot set indexType, invalid index type\n";
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

void IndexHandler::clearTop50Words()
{
    top50Words.clear();
}

void IndexHandler::deleteIndex()
{
    if(index != nullptr)
    {
        delete index;
        index = nullptr;
    }
    numWords = 0;
    numPages = 0;
}

void IndexHandler::clearIndex()
{
    filePaths.clear();
    newPaths.clear();
    top50Words.clear();
    remove(fileName.c_str());
    dp.clearFiles();
    deleteIndex();
}

void IndexHandler::createIndex()
{
    // Don't create index if it already exists
    if(index != nullptr)
        return;

    // Create the type of the index based on the index type
    if(indexType == 1)
        index = new AvlTree;
    else if(indexType == 2){
        index = new MyHash(300000);
    }
    else
        cerr << "Error: Could not create index, invalid index type\n";
    }

void IndexHandler::calculateStats()
{
    // Get the total number of WordRefs in the index
    numWords = index->getNumElements();

    // Get the total number of pages indexed
    numPages = dp.getPagesIndexed();

    // Create a vector of string-int pairs where the string is the word
    // and the int is the corpus frequency for that word
    vector<pair<string,int>> pairs;

    // Create vector of pointers to all wordRefs in index
    vector<WordRef*> refs = index->getIters();

    // Create a pair for each WordRef and add them to a vector
    for(int i=0; i<refs.size(); i++)
    {
        string word = refs[i]->getWord();
        int corpFreq = refs[i]->getCorpusFreq();
        pair<string,int> token = make_pair(word, corpFreq);
        pairs.push_back(token);
    }

    // Sort the vector of string-int pairs based on the int value from greatest to least
    sort(pairs.begin(), pairs.end(), [](const pair<string,int> &left, const pair<string,int> &right)
    {
        if(left.second == right.second)
            return left.first < right.first;
        else
            return left.second > right.second;
    });

    // Copy the top 50 most frequent words to the top50Words vector
    if(pairs.size() <= 50)
        top50Words = pairs;
    else
    {
        for(size_t g=0; g<50; g++)
        {
            top50Words.push_back(pairs[g]);
        }
    }
}

void IndexHandler::writePersistentIndex()
{
    // Don't write persistent index if index is empty
    if(index == nullptr || filePaths.empty())
        return;

    // Open file for output
    persistentIndexFile.open(fileName, ios::out);

    // Verify that file was opened correctly
    if(!persistentIndexFile)
    {
        cerr << "Error: Output file \"" << fileName << "\" was not opened correctly\n";
        exit(EXIT_FAILURE);
    }

    persistentIndexFile << "<persistentIndex>\n";

    // Write file paths to persistent index
    for(int m=0; m<filePaths.size(); m++)
    {
        persistentIndexFile << "<filePath>" << filePaths[m] << "</filePath>\n";
    }

    // Create vector of pointers to all wordRefs in index
    vector<WordRef*> refs = index->getIters();

    // Loop through each WordRef in vector
    for(int i=0; i<refs.size(); i++)
    {
        persistentIndexFile << "<wordRef>\n<word>" << refs[i]->getWord() << "</word>\n";

        // Get the vector of PageLocations for the current WordRef
        vector<PageLocation> pages =refs[i]->getRefs();

        // Loop through each PageLocation in the vector
        for(size_t j=0; j<pages.size(); j++)
        {
            persistentIndexFile << "<pair>\n<id>" << pages[j].getPageID() << "</id>\n";

            // Get the vector of indicies where the word is found in the text
            vector<int> wordIndices = pages[j].getWordIndices();

            persistentIndexFile << "<indices>";

            // Create a space delineated string of the indices
            for(size_t k=0; k<wordIndices.size(); k++)
            {
                persistentIndexFile << wordIndices[k] << " ";
            }

            persistentIndexFile << "</indices>\n</pair>\n";
        }
        persistentIndexFile << "</wordRef>\n";
    }

    persistentIndexFile << "</persistentIndex>";


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
    doc.parse<0>(&xmlFileString[0]);

    // Create the pointers to move around tree, pair has  dummy value
    rapidxml::xml_node<> *pointer = doc.first_node("persistentIndex")->first_node("filePath");
    rapidxml::xml_node<> *pair;
    rapidxml::xml_node<> *elem;

    // Read file paths from the persistent index
    while(pointer != NULL)
    {
        string path = pointer->value();
        dp.addFromPersistent(path);
        addPath(path);
        pointer = pointer->next_sibling("filePath");
    }

    pointer = doc.first_node("persistentIndex")->first_node("wordRef");

    while(pointer != NULL)
    {
        WordRef wr;
        //extracts the necessary imformation from the xml wordRef
        elem = pointer->first_node("word");

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

            // Continue to next pair in current wordRef
            pair = pair->next_sibling("pair");
        }

        // Insert the WordRef into the index
        index->insert(wr);

        // Go to the next wordRef in the
        pointer = pointer->next_sibling("wordRef");
    }
    persistentIndexFile.close();
    doc.clear();
}

WordRef* IndexHandler::searchIndex(std::string& searchWord)
{
    WordRef ref;
    ref.setWord(searchWord);
    return index->searchVal(ref);
}

DocumentParser& IndexHandler::parser()
{
    return dp;
}
