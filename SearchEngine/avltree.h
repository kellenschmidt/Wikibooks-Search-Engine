#ifndef AVLTREE_H
#define AVLTREE_H

template <typename T>
struct TreeNode
{
    T data;
    TreeNode* left;
    TreeNode* right;
};


template<typename var>
class AvlTree
{
private:
    AvlTree():root(nullptr){}
    TreeNode<var>* root;
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
                insert(val, curr->left);
            else
                insert(val, curr->right);
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
};

#endif // AVLTREE_H
