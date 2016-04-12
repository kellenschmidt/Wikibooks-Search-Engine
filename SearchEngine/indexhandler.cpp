#include "indexhandler.h"
#include "documentparser.h"
#include "indexinterface.h"
#include "rapidxml.hpp"
#include <string>
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
    for(int i=0; i<filePaths.size(); i++)
    {
        DocumentParser::parseFile(filePaths[i], *this);
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

void IndexHandler::addWord(string wordToAdd, int id, int pi)
{
    /// Totally not correct needs to be adjusted to fit program
    index->insert(wordToAdd);
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




    persistentIndexFile.close();
}
