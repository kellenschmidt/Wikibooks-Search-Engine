/*
 * File: PageLocation.h
 * Name: Kellen Schmidt
 * Update History:
 * 04/05: File created
 * 04/20: Overloaded < operator
 * 04/29: Included Tf/Idf functionality
 */
#ifndef PAGELOCATION_H
#define PAGELOCATION_H

#include <vector>

class PageLocation
{
private:
    int pageID;
    double tfidf;
    std::vector<int> wordIndices;


public:
    // default constructor, initializes values to default
    PageLocation();
    // constructor setting pageID and wordIndices
    PageLocation(int, std::vector<int>&);
    // sets the pageID
    void setPageID(int);
    // gets the pageID
    int getPageID();
    // sets the Tf/Idf
    void setTfIdf(double);
    // adds a Tf/Idf to the existiong one
    void addTfIdf(double);
    // returns the Tf/Idf
    double getTfIdf();
    // returns by reference the wordIndices vector
    std::vector<int>& getWordIndices();
    // adds a single word index to the wordIndices vector
    void addWordIndex(int);
    // compares two PageLocation objects, returning true if the left one has a smaller Tf/Idf
    friend bool operator <(const PageLocation &l,const PageLocation &r);


};

#endif // PAGELOCATION_H
