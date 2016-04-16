#include "indexhandler.h"
#include "documentparser.h"
#include "indexinterface.h"
#include "wordref.h"
#include "rapidxml.hpp"
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

void IndexHandler::indexPaths()
{
    // Maybe put stopwords into an array instead of reading them from file
    DocumentParser dp("stopwords.txt");
    for(int i=0; i<filePaths.size(); i++)
    {
        dp.parseFile(filePaths[i], index);
    }
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

void IndexHandler::addPath(string newPath)
{
    filePaths.push_back(newPath);
}

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

void IndexHandler::writePersistentIndex()
{
    // Open file for output
    persistentIndexFile.open(fileName, ios::out);

    // Verify that file was opened correctly
    if(!persistentIndexFile)
    {
        cerr << "Error: Output file \"" << fileName << "\" was not opened correctly\n";
        exit(EXIT_FAILURE);
    }




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
                indicesVect.push_back(indexStr);
            }

            // Add the page location data to the WordRef
            wr.insertRef(idInt, indicesVect);

            // Clear vector for new indicies in next pair
            indicesVect.clear();
        }

        // Insert the WordRef into the index
        index.insert(wr);

        // Go to the next wordRef in the
        wordRef = wordRef->next_sibling("wordRef");

        //will need to add the document number and file path to another data structure for lookup
        //add possibly another one for user/editor name, etc..
        //readFromFileIndex();
    }
}
