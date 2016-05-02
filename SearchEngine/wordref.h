/*
 * File: Wordref.h
 * Name: Oscar Vallner
 * Update History:
 * 04/05: File Created
 * 04/20: operators overloaded
 * 04/21: added corpusFreq 
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
    // Initializes values to 0
    WordRef();
    // Sets the word, corpusFreq, and refs to the parameters passed
    WordRef(std::string, int, std::vector<PageLocation>&);
    // Sets the word 
    void setWord(std::string);
    // Returns the word
    std::string getWord() const;
    // sets the corpus frequency
    void setCorpusFreq(int);
    // returns the corpus frequency
    int getCorpusFreq();
    // returns the Refs vector of PageLocations
    std::vector<PageLocation>& getRefs();
    // inserts a PageLocation into the Refs vector
    void insertRef(int, std::vector<int>&);
    // returns true if the WordRef on the left's word is smaller than the right's
    bool operator<(WordRef);
    // returns true if the WordRefs have the same word
    bool operator==(WordRef);
    // prints out the word of the WordRef
    friend std::ostream& operator<<(std::ostream&, WordRef);
    // sorts Refs
    void sortRefs();
};

#endif // WORDREF_H
