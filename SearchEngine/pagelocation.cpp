#include "pagelocation.h"
#include <vector>
#include <iostream>

using namespace std;

PageLocation::PageLocation()
{
    pageID = 0;
    wordIndices = {};
}

PageLocation::PageLocation(int pi, vector<int>& indices)
{
    setPageID(pi);
    wordIndices = indices;
}

void PageLocation::setPageID(int pi)
{
    if(pi >= 0)
        pageID = pi;
    else
        cerr << "Error: Cannot set page ID, pageID is either negative or out of range\n";
}

int PageLocation::getPageID()
{
    return pageID;
}

void PageLocation::setTfIdf(double arg)
{
    tfidf = arg;
}

void PageLocation::addTfIdf(double arg)
{
    tfidf += arg;
}
double PageLocation::getTfIdf()
{
    return tfidf;
}

vector<int>& PageLocation::getWordIndices()
{
    return wordIndices;
}

void PageLocation::addWordIndex(int newIndex)
{
    wordIndices.push_back(newIndex);
}


