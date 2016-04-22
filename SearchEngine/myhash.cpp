#include "myhash.h"

using namespace std;

MyHash::MyHash()
{
    buckets = 100;
    occupied = 0;
    table = new AvlTree[buckets];
}

MyHash::MyHash(int maxBuckets)
{
    buckets = maxBuckets;
    occupied = 0;
    table = new AvlTree[buckets];
}

MyHash::~MyHash()
{
    if(table!=nullptr)
        delete table;
}

WordRef* MyHash::searchVal(WordRef &val)
{
    //cout << "hash search called" << endl;
    //hash the string and then search the AvlTree for the string to see if it is there
    int hashVal = strHash(val.getWord())%buckets;
    return table[hashVal].searchVal(val);
}

void MyHash::insert(WordRef & toInsert)
{
    //cout << "hash insert called" << endl;
    //hash the string and put it in the array that is already thaere
    int hashVal = strHash(toInsert.getWord())%buckets;
    table[hashVal].insert(toInsert);
}

