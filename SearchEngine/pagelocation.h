#ifndef PAGELOCATION_H
#define PAGELOCATION_H

#include <vector>

class PageLocation
{
private:
    int pageID;
    std::vector<int> wordIndices;

public:
    PageLocation();
    PageLocation(int, std::vector<int>);
    void setPageID(int);
    int getPageID();
    void addWordIndex(int);
};

#endif // PAGELOCATION_H
