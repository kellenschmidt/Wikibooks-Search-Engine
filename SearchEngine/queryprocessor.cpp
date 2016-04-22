#include "queryprocessor.h"
#include <sstream>
#include <algorithm>

using namespace std;

QueryProcessor::QueryProcessor()
{

}

QueryProcessor::QueryProcessor(IndexHandler &arg)
{
    handler = &arg;
}

void QueryProcessor::setHandler(IndexHandler &arg)
{
    handler = &arg;
}

void QueryProcessor::processQuery(string &query)
{
    stringstream ss;
    string word;

    ss << query;
    ss >> word;
    stem(word);

    WordRef* temp = findWord(word);
    if(temp == nullptr)
        cout << "Word not found\n";
    else
        findPages(temp);
}

WordRef* QueryProcessor::findWord(std::string &word)
{
    return handler->searchIndex(word);
}

void QueryProcessor::stem(string &word)
{
    Porter2Stemmer::stem(word);
}

void QueryProcessor::findPages(WordRef* ref)
{
    vector<PageLocation> results = ref->getRefs();

    sort(results.begin(), results.end());

    vector<PageLocation> locs;
    int maxSize =results.size();
    for(int i=results.size()-1;i>0 && i>maxSize-16 ;i--)
    {
        locs.push_back(results.at(i));
    }
    //locs
    printPages(results);
}

void QueryProcessor::printPages(vector<PageLocation> &results)
{
    for(int i = 0; i < results.size(); i++)
    {
        cout << i + 1 << ": \n\tid: " << results[i].getPageID() << "\n\tOccurences: " << results[i].getWordIndices().size() << "\n";
    }
}

bool operator<(const PageLocation &l, const PageLocation &r)
{
    return l.wordIndices.size() < r.wordIndices.size();
}
