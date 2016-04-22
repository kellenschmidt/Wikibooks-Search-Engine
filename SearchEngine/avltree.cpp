#include <iostream>
#include "indexinterface.h"
#include "wordref.h"
#include "avltree.h"

using namespace std;

////////////////PUBLIC FUNCTIONS//////////////////////////////////////
///

// a method that inserts a value into the appropriate position in 
// the tree
void AvlTree::insert(WordRef &val)
{
    insert(val, root);
}

// a method that returns true if a value exists in the tree
// and false if it does not
WordRef* AvlTree::searchVal(WordRef &val)
{
    return searchVal(val,root);
}

WordRef* AvlTree::searchVal(string &val)
{
    return searchVal(val, root);
}

// returns the height of a specified node
// Val is the value of an existing node
// only works if val exists in the tree
int AvlTree::nodeHeight(WordRef &val)
{
    int counter = 0;
    std::cout << "counter: " << counter << "\n";
    heightHelper(val, root, counter);
    std::cout << "counterend: " << counter << "\n";
    return counter;
}

////////////////PRIVATE FUNCTIONS/////////////////////////////////////
///
TreeNode* AvlTree::rr_rotation(TreeNode* parent)
{
        //std::cout << "rr\n";
    TreeNode* temp = parent->right;
    parent->right = temp->left;
    temp->left = parent;
    return temp;
}


TreeNode* AvlTree::ll_rotation(TreeNode* parent)
{
        //std::cout << "ll\n";
    TreeNode* temp = parent->left;
    parent->left = temp->right;
    temp->right = parent;
    return temp;
}


TreeNode* AvlTree::lr_rotation(TreeNode* parent)
{
        //std::cout << "lr\n";
    TreeNode* temp = parent->left;
    parent->left = rr_rotation(temp);
    return ll_rotation(parent);
}

TreeNode* AvlTree::rl_rotation(TreeNode* parent)
{
        //std::cout << "rl\n";
    TreeNode* temp = parent->right;
    parent->right = ll_rotation(temp);
    return rr_rotation(parent);
}

int AvlTree::height(TreeNode* curr)
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

int AvlTree::height_Diff(TreeNode* curr)
{
    int l_height = height(curr->left);
    int r_height = height(curr->right);
    int diff = l_height - r_height;
    return diff;
}

TreeNode* AvlTree::balance(TreeNode* curr)
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

void AvlTree::heightHelper(WordRef val, TreeNode* &curr, int &counter)
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
    else if(curr->data < val)
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

void AvlTree::insert(WordRef val, TreeNode* &curr)
{
    if(curr==nullptr)
    {
            //std::cout << "val" << val << "\n";
        TreeNode* leaf = new TreeNode;
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

WordRef* AvlTree::searchVal(WordRef &val, TreeNode* curr)
{
    if(curr == nullptr)
        return nullptr;
    if(curr-> data == val)
    {
        //temp = &curr->data;
        return &curr->data;
    }
    if(val < curr->data)
    {
        if(curr->left != nullptr)
            return searchVal(val, curr->left);
        else
        {
            return nullptr;
        }
    }
    else
    {
        if(curr->right != nullptr)
            return searchVal(val, curr->right);
        else
            return nullptr;
    }
}

WordRef* AvlTree::searchVal(string &val, TreeNode* curr)
{
    if(curr == nullptr)
        return nullptr;
    if(curr->data.getWord() == val)
    {
        return &curr->data;
    }
    if(val < curr->data.getWord())
    {
        if(curr->left != nullptr)
            return searchVal(val, curr->left);
        else
        {
            return nullptr;
        }
    }
    else
    {
        if(curr->right != nullptr)
            return searchVal(val, curr->right);
        else
            return nullptr;
    }
}
