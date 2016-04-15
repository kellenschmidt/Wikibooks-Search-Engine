/*
 * File: Wordref.cpp
 * Name: Kellen Schmidt
 * Update History:
 *
 */

#include "pagelocation.h"
#include "wordref.h"

using namespace std;

WordRef::WordRef()
{
    corpusFreq = 0;
}

void WordRef::setWord(std::string w)
{
    word = w;
}

std::string WordRef::getWord()
{
    return word;
}

void WordRef::setCorpusFreq(int cf)
{
    corpusFreq = cf;
}

long WordRef::getCorpusFreq()
{
    return corpusFreq;
}

void WordRef::insertRef(int pageID, int wordIndex)
{
    // Add the word index to the set of word indices located at pageID
    ///if(pageID)
    // Increment the number of times the word is found in the corpus
    corpusFreq++;
}
