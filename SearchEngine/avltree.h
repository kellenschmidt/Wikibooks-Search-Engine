// AvlTree.h
//
#include <iostream>

using namespace std;
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

    //Rotations Begin
    TreeNode<var>* rr_rotation(TreeNode<var>* parent)
    {
        TreeNode<var>* temp = parent->right;
        parent->right = temp->left;
        temp->left = parent;
        return temp;
    }

    TreeNode<var>* ll_rotation(TreeNode<var>* parent)
    {
        TreeNode<var>* temp = parent->left;
        parent->left = temp->right;
        temp->right = parent;
        return temp;
    }

    TreeNode<var>* lr_rotation(TreeNode<var>* parent)
    {
        TreeNode<var>* temp = parent->left;
        parent->left = rr_rotation(temp);
        return ll_rotation(parent);
    }

    TreeNode<var>* rl_rotation(TreeNode<var>* parent)
    {
        TreeNode<var>* temp = parent->right;
        parent->right = ll_rotation(temp);
        return rr_rotation(parent);
    }

    //Rotations end
    int height(TreeNode<var>* curr)
    {
        int h = 0;
        if(curr!= NULL)
        {
            int l_height = height(curr->left);
            int r_height = height(curr->right);
            int max_height = max(l_height, r_height);
            h = max_height + 1;
        }
        return h;
    }

    int height_Diff(TreeNode<var>* curr)
    {
        int l_height = height(curr->left);
        int r_height = height(curr->right);
        int diff = l_height - r_height;
        return diff;
    }

    TreeNode<var>* balance(TreeNode<var>* curr)
    {
        int bal_factor = height_Diff(curr);
        if(bal_factor > 1)
        {
            if(height_Diff(curr->left) > 0)
                curr = ll_rotation(curr);
            else
                curr = lr_rotation(curr);
        }
        else if(bal_factor < -1)
        {
            if(height_Diff(curr->right) > 0)
                curr = rl_rotation(curr);
            else
                curr = rr_rotation(curr);
        }
        return curr;
    }

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
            TreeNode<var>* leaf = new TreeNode<var>;
            leaf->data = val;
            curr = leaf;
        }
        else
        {
            if(val < curr->data)
            {
                insert(val, curr->left);
                curr = balance(curr);
            }
            if(curr->data < val)
            {
                insert(val, curr->right);
                curr = balance(curr);
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
