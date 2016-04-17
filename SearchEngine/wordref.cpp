/*
 * File: Wordref.cpp
 * Name: Kellen Schmidt
 * Update History:
 *
 */

#include "pagelocation.h"
#include "wordref.h"
#include <iostream>
#include <vector>

using namespace std;

WordRef::WordRef()
{
    setWord("");
    setCorpusFreq(0);
    refs = {};
}

WordRef::WordRef(string w, int cf, const vector<PageLocation>& ref)
{
    setWord(w);
    setCorpusFreq(cf);
    refs = ref;
}

void WordRef::setWord(string w)
{
    word = w;
}

std::string WordRef::getWord() const
{
    return word;
}

void WordRef::setCorpusFreq(int cf)
{
    if(cf >= 0)
        corpusFreq = cf;
    else
        cerr << "Error: Cannot set corpus frequency, corpusFreq is either negative or out of range\n";
}

int WordRef::getCorpusFreq()
{
    return corpusFreq;
}

vector<PageLocation> WordRef::getRefs() const
{
    return refs;
}

void WordRef::insertRef(int pageID, const vector<int>& indices)
{
    // Create PageLocation object from arguments and add it to vector
    PageLocation pl(pageID, indices);
    refs.push_back(pl);

    // Add the number of new indicies to the total corpus frequency
    corpusFreq+=indices.size();
}

bool WordRef::operator<(WordRef ref)
{
    return word < ref.getWord();
}

bool WordRef::operator==(WordRef ref)
{
    return word == ref.getWord();
}

ostream& operator<<(ostream& os, WordRef ref)
{
    return os << ref.word << "\n";
}
