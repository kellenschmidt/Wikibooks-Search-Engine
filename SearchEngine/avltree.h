// AvlTree.h
//
#include <iostream>

#ifndef AVLTREE_H
#define AVLTREE_H

template <typename T>
struct TreeNode
{
    T data;
    TreeNode* left = nullptr;
    TreeNode* right = nullptr;
};


template<typename var>
class AvlTree
{
private:
    TreeNode<var>* root;


    void heightHelper(var val, TreeNode<var>* &curr, int &counter)
    {
        if(curr->data == val)
            return;
        if(val < curr->data)
        {
            if(curr->left != nullptr)
            {
                counter++;
                heightHelper(val, curr->left, counter);
            }
            else
                return;
        }
        else
        {
            if(curr->right != nullptr)
            {
                counter++;
                heightHelper(val, curr->right, counter);
            }
            else
                return;
        }
    }

    void insert(var val, TreeNode<var>* &curr)
    {
        if(curr==nullptr)
        {
            std::cout << "val" << val << "\n";
            TreeNode<var>* leaf = new TreeNode<var>;
            leaf->data = val;
            curr = leaf;
        }
        else
        {
            if(val < curr->data)
            {
                std::cout << "branch left\n";
                insert(val, curr->left);
            }
            if(curr->data < val)
            {
                std::cout << "branch right\n";
                insert(val, curr->right);
            }
        }
    }

    bool searchVal(var val, TreeNode<var>* &curr)
    {
        if(curr-> data == val)
            return true;
        if(val < curr->data)
        {
            if(curr->left != nullptr)
                searchVal(val, curr->left);
            else
                return false;
        }
        else
        {
            if(curr->right != nullptr)
                searchVal(val, curr->right);
            else
                return false;
        }
    }
public:

    AvlTree():root(nullptr){}
    // a method that inserts a value into the appropriate position in 
    // the tree
    void insert(var val)
    {
        insert(val, root);
    }

    // a method that returns true if a value exists in the tree
    // and false if it does not
    bool searchVal(var val)
    {
        return searchVal(val, root);
    }

    // returns the height of a specified node
    // Val is the value of an existing node
    // only works if val exists in the tree
    int nodeHeight(var val)
    {
        int counter = 0;
        heightHelper(val, root, counter);
        return counter;
    }
};

#endif // AVLTREE_H
