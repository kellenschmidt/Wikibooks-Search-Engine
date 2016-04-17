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
    PageLocation(int, const std::vector<int>&);
    void setPageID(int);
    int getPageID();
    std::vector<int> getWordIndices();
    void addWordIndex(int);
};

#endif // PAGELOCATION_H
