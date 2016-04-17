#include "indexhandler.h"
#include "documentparser.h"
///#include "indexinterface.h"
#include "wordref.h"
#include "rapidxml.hpp"
#include "rapidxml_print.hpp"
#include <string>
#include <sstream>
#include <iostream>
#include <fstream>

using namespace std;

IndexHandler::IndexHandler()
{
    indexType = 0;
    fileName = "Persistent Index.txt";
}

vector<WordRef> IndexHandler::indexPaths(const vector<string>& paths)
{
    /// Maybe put stopwords into an array instead of reading them from file
    DocumentParser dp("stopwords.txt");

    // Create vector to store all of the WordRefs that are indexed
    vector<WordRef> refs;
    // Create vector to store the most recently indexed WordRefs
    vector<WordRef> newRefs;

    // Parse the xml file at each path
    // Get the new WordRefs that are indexed and add them to the vector of all new WordRefs
    for(size_t i=0; i<paths.size(); i++)
    {
        ///dp.parseFile(paths[i], index, newRefs);
        refs.insert(refs.end(), newRefs.begin(), newRefs.end());
    }
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

vector<string>& IndexHandler::getPaths()
{
    return filePaths;
}

vector<string>& IndexHandler::getNewPaths()
{
    return newPaths;
}

void IndexHandler::addPath(string newPath)
{
    filePaths.push_back(newPath);
}

void IndexHandler::addNewPath(string newPath)
{
    newPaths.push_back(newPath);
}

void IndexHandler::clearPaths()
{
    filePaths.clear();
    newPaths.clear();
}

/**
void IndexHandler::createIndex()
{
    // Create the type of the index based on the index type
    if(indexType == 1)
        index = new AvlTree<wordRef>;
    else if(indexType == 2)
        index = new HashTableIndex;
    else
        cerr << "Error: Could not create index, invalid index type\n";
}
**/
void IndexHandler::writePersistentIndex(const vector<WordRef>& wordRefs)
{
    // Open file if there aren't any WordRef
    if(filePaths.empty())
    {
        // Open file for output
        persistentIndexFile.open(fileName, ios::out);

        // Verify that file was opened correctly
        if(!persistentIndexFile)
        {
            cerr << "Error: Output file \"" << fileName << "\" was not opened correctly\n";
            exit(EXIT_FAILURE);
        }
    }

    rapidxml::xml_document<> doc;
    for(size_t i=0; i<wordRefs.size(); i++)
    {
        rapidxml::xml_node<> *wordRef = doc.allocate_node(rapidxml::node_element, "wordRef");
        rapidxml::xml_attribute<> *word = doc.allocate_attribute("word", wordRefs[i].getWord().c_str());
        wordRef->append_attribute(word);
        vector<PageLocation> refs = wordRefs[i].getRefs();
        for(size_t j=0; j<refs.size(); j++)
        {
            rapidxml::xml_node<> *pair = doc.allocate_node(rapidxml::node_element, "pair");
            rapidxml::xml_attribute<> *id = doc.allocate_attribute("id", to_string(refs[j].getPageID()).c_str());
            pair->append_attribute(id);
            vector<int> wordIndices = refs[j].getWordIndices();
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
