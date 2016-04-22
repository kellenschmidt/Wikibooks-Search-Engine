#ifndef QUERYPROCESSOR_H
#define QUERYPROCESSOR_H

#include "indexhandler.h"
#include "porter2_stemmer.h"

class QueryProcessor
{
public:
    QueryProcessor();
    QueryProcessor(IndexHandler &);
    void setHandler(IndexHandler &);
    void processQuery(std::string &);
private:
    IndexHandler* handler;
    WordRef* findWord(std::string &);
    void stem(std::string &);
    void findPages(WordRef*);
    void printPages(std::vector<PageLocation> &);
    bool compareLocs(const PageLocation&l,const PageLocation&r);
};

#endif // QUERYPROCESSOR_H
