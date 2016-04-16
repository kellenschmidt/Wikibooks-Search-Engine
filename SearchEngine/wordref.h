/*
 * File: Wordref.h
 * Name: Kellen Schmidt
 * Update History:
 *
 */

#ifndef WORDREF_H
#define WORDREF_H

#include "pagelocation.h"
#include <iostream>
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
    WordRef(std::string, int, std::vector<PageLocation>);
    void setWord(std::string);
    std::string getWord();
    void setCorpusFreq(int);
    int getCorpusFreq();
    void insertRef(int, std::vector<int>);
    bool operator<(WordRef);
    bool operator==(WordRef);
    friend std::ostream& operator<<(std::ostream&, WordRef);
};

#endif // WORDREF_H
