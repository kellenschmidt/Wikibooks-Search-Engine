#ifndef PAGELOCATION_H
#define PAGELOCATION_H

#include <vector>

class PageLocation
{
private:
    int pageID;
    //std::vector<int> wordIndices;
    //TODO make private!!!!

public:
    std::vector<int> wordIndices;
    PageLocation();
    PageLocation(int, std::vector<int>&);
    void setPageID(int);
    int getPageID();
    std::vector<int>& getWordIndices();
    void addWordIndex(int);
    friend bool operator <(const PageLocation &l,const PageLocation &r);

};

#endif // PAGELOCATION_H
