/*
 * File: myhash.h
 * Name: Luke Hansen
 * Update history:
 * 4/13/16 - File and class created
 * 4/20/16 - Major updates to implementation
 * 4/25/16 - Began using AVLTrees instead ofl linked list
 * 4/28/16 - Implemented traversal to obtain all elements
 */

#ifndef MYHASH_H
#define MYHASH_H

#include "indexinterface.h"
#include "avltree.h"
#include "wordref.h"
#include <vector>

class MyHash:public IndexInterface
{
public:
    // Create and set default values
    MyHash();

    // Create and set size to maxBuckets
    MyHash(int maxBuckets);

    // Deallocate dynamically allocated memory
    ~MyHash();

    // Insert WordRef into hash table
    void insert(WordRef &);

    // Return pointer to WordRef found in the hash table
    WordRef* searchVal(WordRef&);

    // Return number of elements in hash table
    int getNumElements();

    // Return the number of buckets in hash table
    int getNumBuckets();

    // Return the array of all the AvlTrees in the buckets
    AvlTree* getTable();

    // Return vector of all the elements in the hash table
    std::vector<WordRef*>& getIters();
private:
    std::hash<std::string> strHash;
    AvlTree *table;
    int buckets;
    int numInserted;
    std::vector<WordRef*> iters;

};

#endif // HASHTABLE_H
