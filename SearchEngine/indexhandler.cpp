#include "indexhandler.h"
#include "documentparser.h"
#include "indexinterface.h"
#include <string>
#include <iostream>

using namespace std;

IndexHandler::IndexHandler()
{

}

void IndexHandler::indexPaths()
{
    for(int i=0; i<filePaths.size(); i++)
    {
        DocumentParser::parseFile(filePaths[i]);
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
        IndexInterface *index = new AvlTree<wordRef>;
    else if(indexType == 2)
        IndexInterface *index = new HashTableIndex;
    else
        cerr << "Error: Could not create index, invalid index type\n";
}
