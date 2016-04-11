/*
 * File: Wordref.h
 * Name: Kellen Schmidt
 * Update History:
 *
 */

#ifndef WORDREF_H
#define WORDREF_H

#include "pagelocation.h"
#include <string>
#include <unordered_map>
#include <list>

class WordRef
{
private:
    std::string word;
    std::unordered_map<long, std::list<long>> refs;
    long corpusFreq;

public:
    WordRef();
    void setWord(std::string);
    std::string getWord();
    void setCorpusFreq(long);
    long getCorpusFreq();
    void insertRef(long, long);
};

#endif // WORDREF_H
