#include "pagelocation.h"
#include <vector>
#include <iostream>

using namespace std;

PageLocation::PageLocation()
{
    pageID = 0;
}

PageLocation::PageLocation(int pi, const vector<int>& indices)
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

vector<int> PageLocation::getWordIndices()
{
    return wordIndices;
}

void PageLocation::addWordIndex(int newIndex)
{
    wordIndices.push_back(newIndex);
}
