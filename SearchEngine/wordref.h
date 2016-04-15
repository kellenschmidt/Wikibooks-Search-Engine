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
#include <vector>

class WordRef
{
private:
    std::string word;
    std::vector<PageLocation> refs;
    int corpusFreq;

public:
    WordRef();
    void setWord(std::string);
    std::string getWord();
    void setCorpusFreq(int);
    int getCorpusFreq();
    // Not implemented yet
    void insertRef(int, int);
};

#endif // WORDREF_H
