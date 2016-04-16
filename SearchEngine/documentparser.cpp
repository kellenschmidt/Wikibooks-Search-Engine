#include "documentparser.h"
//#include "indexinterface.h"
#include "wordref.h"
#include "avltree.h"
#include <iostream>

using namespace std;

DocumentParser::DocumentParser()
{

}

void DocumentParser::parseFile(int indexType)
{
    // Create the type of the index based on the index type
    if(indexType == 1)
        IndexInterface *index = new AvlTree<WordRef>;
    else if(indexType == 2)
        //Type dependent on Luke
        IndexInterface *index = new HashTableIndex;
    else
        cerr << "Error: Could not create index, invalid index type\n";


}
