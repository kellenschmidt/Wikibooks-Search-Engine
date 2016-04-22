// IndexInterface.h
//
//#include "avltree.h"
#include "wordref.h"
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
    virtual void insert(WordRef &){}
    virtual int nodeHeight(WordRef){}
    virtual WordRef* searchVal(WordRef &){}
    virtual WordRef* searchVal(std::string &){}
};

#endif // INDEXINTERFACE_H
