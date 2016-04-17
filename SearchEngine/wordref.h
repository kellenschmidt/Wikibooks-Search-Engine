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
    int corpusFreq;
    std::vector<PageLocation> refs;

public:
    WordRef();
    WordRef(std::string, int, const std::vector<PageLocation>&);
    void setWord(std::string);
    std::string getWord() const;
    void setCorpusFreq(int);
    int getCorpusFreq();
    std::vector<PageLocation> getRefs() const;
    void insertRef(int, const std::vector<int>&);
    bool operator<(WordRef);
    bool operator==(WordRef);
    friend std::ostream& operator<<(std::ostream&, WordRef);
};

#endif // WORDREF_H
