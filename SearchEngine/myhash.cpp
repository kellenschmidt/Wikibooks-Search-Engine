#include "myhash.h"

using namespace std;

MyHash::MyHash()
{
    cout << "myhach created" << endl;
    buckets = 100;
    numInserted = 0;
    table = new AvlTree[buckets];
}

MyHash::MyHash(int maxBuckets)
{
    buckets = maxBuckets;
    numInserted = 0;
    table = new AvlTree[buckets];
}

MyHash::~MyHash()
{
    if(table!=nullptr)
        delete table;
    cout << "myhash deleted" << endl;
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
    numInserted++;
    iters.push_back(table[hashVal].searchVal(toInsert));
}

int MyHash::getNumElements()
{
    cout << "mehh" << endl;
    return numInserted;
}

int MyHash::getNumBuckets()
{
    return buckets;
}

AvlTree* MyHash::getTable(){
    return table;
}


vector<WordRef*>& MyHash::getIters()
{
    return iters;
}

