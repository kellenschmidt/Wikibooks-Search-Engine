/*
 * File: QueryProcessor.h
 * Name: Oscar Vallner
 * Update History:
 * 04/20: created
 * 04/21: able to do 1 word searches
 * 04/28: able to do OR searches
 * 04/29: able to do AND searches
 * 04/30: able to do NOT
 * 05/01: bug fixes
 *
 */
#ifndef QUERYPROCESSOR_H
#define QUERYPROCESSOR_H

#include "indexhandler.h"
#include "porter2_stemmer.h"
#include <algorithm>

class QueryProcessor
{
public:
    // Default constructor
    QueryProcessor();
    // Constructor that sets gives it the correct IndexHandler to use
    QueryProcessor(IndexHandler &);
    // sets IndexHandler if the user use the default constructor or wants to change
    void setHandler(IndexHandler &);
    // accepts a string query and processes it, resulting in a vector of PageLocations
    void processQuery(std::string &);
    // returns the PageLocations from the processed query
    std::vector<PageLocation>& getResults();
    // clears the result from the previously processed query. Use this before every new processQuery
    void clearResults();
private:
    IndexHandler* handler;
    std::vector<PageLocation> trimmedSet;
    WordRef* findWord(std::string &);
    WordRef* findPhrase(std::vector<std::string>);
    void processWord(std::string &);
    void process2Words(std::string &, std::string&);
    void processAnd(std::vector<std::string> &);
    std::vector<PageLocation>* processOr(std::vector<std::string> &);
    void processNot(std::vector<std::string> &);
    void stem(std::string &);
    std::vector<PageLocation>& findPages(WordRef*);
    void printPages(std::vector<PageLocation> &);
    bool compareLocs(const PageLocation&l,const PageLocation&r);
    void calcTfIdf(PageLocation&, WordRef*);
};

#endif // QUERYPROCESSOR_H
