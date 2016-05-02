/* 
 * File: AvlTree.h
 * Name: Oscar Vallner
 * Update History:
 * 04/09: File created
 * 04/10: Binary tree funtionality
 * 04/11: AVLTree functionality (rebalancing)
 * 04/20: Added numElements and a getter method
 * 04/27: Moved Iterator functionality to the class
 *
 */
#include <iostream>
#include "indexinterface.h"
#include "wordref.h"
#include <vector>
#ifndef AVLTREE_H
#define AVLTREE_H



class AvlTree: public IndexInterface
{
private:
    TreeNode* root;

    int numElements;

    std::vector<WordRef*> iters;

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

    //default constructor that initializes values
    AvlTree():root(nullptr),numElements(0){}

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

    // returns the number of elements in the tree
    int getNumElements();

    // returns the root
    TreeNode* getRoot();

    // returns a vector containing of the data stored in all of the nodes
    std::vector<WordRef*>& getIters();
};

#endif // AVLTREE_H
