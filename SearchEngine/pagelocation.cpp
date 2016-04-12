#include "pagelocation.h"
#include <vector>

PageLocation::PageLocation()
{
    pageID = 0;
}

void PageLocation::setPageID(int pi)
{
    pageID = pi;
}

int PageLocation::getPageID()
{
    return pageID;
}

void PageLocation::addWordIndex(int newIndex)
{
    wordIndices.push_back(newIndex);
}
