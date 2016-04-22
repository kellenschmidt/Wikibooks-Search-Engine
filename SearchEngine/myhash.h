#ifndef MYHASH_H
#define MYHASH_H

#include "indexinterface.h"
#include "avltree.h"
#include "wordref.h"
class MyHash:public IndexInterface
{
public:
    MyHash();
    MyHash(int maxBuckets);
    ~MyHash();
    void insert(WordRef &);
    WordRef* searchVal(WordRef&);
private:
    std::hash<std::string> strHash;
    AvlTree *table;
    int buckets;
    int occupied;

};

#endif // HASHTABLE_H
