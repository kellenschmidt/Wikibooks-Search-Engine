// AvlTree.h
//
#include <iostream>
#include "indexinterface.h"
#include "wordref.h"
#ifndef AVLTREE_H
#define AVLTREE_H

/*struct TreeNode
{
    WordRef data;
    TreeNode* left = nullptr;
    TreeNode* right = nullptr;
};*/


class AvlTree: public IndexInterface
{
private:
    TreeNode* root;

    //Rotations Begin
    TreeNode* rr_rotation(TreeNode*);
    TreeNode* ll_rotation(TreeNode*);
    TreeNode* lr_rotation(TreeNode*);
    TreeNode* rl_rotation(TreeNode*);
    //Rotations end

    int height(TreeNode*);
    int height_Diff(TreeNode*);
    TreeNode* balance(TreeNode*);
    void heightHelper(WordRef, TreeNode* &, int &);
    void insert(WordRef, TreeNode* &);
    WordRef* searchVal(WordRef &, TreeNode*);
    WordRef* searchVal(std::string &, TreeNode*);

public:

    AvlTree():root(nullptr){}
    // a method that inserts a value into the appropriate position in 
    // the tree
    void insert(WordRef &);
    
    // a method that returns true if a value exists in the tree
    // and false if it does not
    WordRef* searchVal(WordRef &);
    WordRef* searchVal(std::string &);

    // returns the height of a specified node
    // Val is the value of an existing node
    // only works if val exists in the tree
    int nodeHeight(WordRef &);
};

#endif // AVLTREE_H
