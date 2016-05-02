/* File: IndexInterface.h
 * Name: Oscar Vallner
 * Update History:
 * 04/05: created
 * 04/15: added getNumElements and getRoot
 * 04/26: added getIters
 */

#include "wordref.h"
#include <vector>
#ifndef INDEXINTERFACE_H
#define INDEXINTERFACE_H


struct TreeNode
{
    WordRef data;
    TreeNode* left = nullptr;
    TreeNode* right = nullptr;
};

class IndexInterface
{
public:
    // inserts a WordRef into the structure
    virtual void insert(WordRef &){}

    // searches the structure for a WordRef and returns a pointer to it
    virtual WordRef* searchVal(WordRef &){}
    virtual WordRef* searchVal(std::string &){}

    // returns a vector containing all of the elements contained in a structure
    virtual std::vector<WordRef*>& getIters(){}

    // for avl tree only
    virtual int nodeHeight(WordRef){}
    virtual TreeNode* getRoot(){}
    virtual int getNumElements(){}
};

#endif // INDEXINTERFACE_H
