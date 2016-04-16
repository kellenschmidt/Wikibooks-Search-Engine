#include "pagelocation.h"
#include <vector>
#include <iostream>

using namespace std;

PageLocation::PageLocation()
{
    pageID = 0;
}

PageLocation::PageLocation(int pi, vector<int> indices)
{
    setPageID(pi);
    wordIndices = indices;
}

void PageLocation::setPageID(int pi)
{
    if(pi >= 0 && pi <= 2147483648)
        pageID = pi;
    else
        cerr << "Error: Cannot set page ID, pageID is either negative or out of range\n";
}

int PageLocation::getPageID()
{
    return pageID;
}

void PageLocation::addWordIndex(int newIndex)
{
    wordIndices.push_back(newIndex);
}
