#include "queryprocessor.h"
#include <sstream>
#include <algorithm>
#include <cctype>

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

    vector<string> wordVect;
    ss << query;
    while(ss)
    {
        ss >> word;
        wordVect.push_back(word);
    }
    wordVect.pop_back();

    // processes all the words to a usable format
    for(int i = 0; i < wordVect.size(); i++)
    {
        processWord(wordVect[i]);
    }
    if(wordVect.size() == 1)
    {
        WordRef* temp = findWord(wordVect[0]);
        if (temp != nullptr)
            trimmedSet = findPages(temp);
    }
    for(int i = 0; i < wordVect.size(); i++)
    {
        if(wordVect.size() == 1)
            break;
        string boolOp = "";
        vector<string> opVect;
        if(isupper(wordVect[i][0]))
        {
            opVect.clear();
            boolOp = wordVect[i++];
            while(i != wordVect.size() && (!isupper(wordVect[i][0]) || wordVect[i][0] == '['))
            {
                if(findWord(wordVect[i]) != nullptr || wordVect[i][0] == '[' || wordVect[i][wordVect[i].size() -1] == ']')
                    opVect.push_back(wordVect[i++]);
                else
                    i++;
            }

            if(boolOp == "AND" && opVect.size() > 1)
                processAnd(opVect);

            if(boolOp == "OR" && opVect.size() > 1)
                processOr(opVect);
            if(opVect.size() == 1)
            {
                WordRef* temp = findWord(opVect[0]);
                trimmedSet = findPages(temp);
            }
        }
        else
        {
            while(i != wordVect.size() && !isupper(wordVect[i][0]))
            {
                if(findWord(wordVect[i]) != nullptr)
                {
                    WordRef* temp = findWord(wordVect[i++]);
                    trimmedSet = findPages(temp);
                }
                else 
                    i++;
            }
        }
        if(i < wordVect.size())
        {
            if(wordVect[i] == "NOT")
            {
                i++;
                vector<string> notVect;
                for(i; i < wordVect.size(); i++)
                    notVect.push_back(wordVect[i]);

                processNot(notVect);
            }
        }
        if(opVect.size() == 0)
            cout << "No valid words entered\n";
    }
    sort(trimmedSet.begin(), trimmedSet.end());
    reverse(trimmedSet.begin(), trimmedSet.end());
}

void QueryProcessor::processWord(string &word)
{
    if(word == "or" || word == "OR" || word == "Or")
        transform(word.begin(), word.end(), word.begin(), ::toupper);

    else if(word == "and" || word == "AND" || word == "And")
        transform(word.begin(), word.end(), word.begin(), ::toupper);
    
    else if(word == "not" || word == "NOT" || word == "Not")
        transform(word.begin(), word.end(), word.begin(), ::toupper);

    else
    {
        stem(word);
        transform(word.begin(), word.end(), word.begin(), ::tolower);
    }
}

void QueryProcessor::process2Words(string &word1, string &word2)
{
    processWord(word1);
    processWord(word2);
}

WordRef* QueryProcessor::findPhrase(vector<string> phraseWords)
{
    WordRef* phrase = new WordRef;
    vector<WordRef*> phraseRef;
    phraseWords[0].erase(phraseWords[0].begin());
    phraseWords[phraseWords.size() -1].erase(phraseWords[phraseWords.size() - 1].begin() + phraseWords[phraseWords.size() -1].size() - 1);
    stem(phraseWords[phraseWords.size() -1]);
    for(int i = 0; i < phraseWords.size(); i++)
    {
        WordRef* temp; //= new WordRef;
        temp = findWord(phraseWords[i]);
        phraseRef.push_back(temp);
    }
    // creates a base set that other sets will remove from
    phrase->getRefs() = phraseRef[0]->getRefs();

    // loops through each of the WordRef*
    for(int i = 1; i < phraseRef.size(); i++)
    {
        // loops through the page location vector of phrase
        for(int j = 0; j < phrase->getRefs().size(); j++)
        {
            int pID = phrase->getRefs()[j].getPageID();
            bool idFound = false;
            // loops through the page location vector of phraseRef[i]
            for(int k = 0; k < phraseRef[i]->getRefs().size(); j++)
            {
                // checks if the words are on the same page
                if(pID == phraseRef[i]->getRefs()[k].getPageID())
                {
                    idFound = true;
                    // loops through the word Indices of phrase->getRefs()[k]
                    for(int l = 0; l < phrase->getRefs()[j].getWordIndices().size(); l++)
                    {
                        int targetLoc = (phrase->getRefs()[j].getWordIndices()[l]) + 1;
                        bool targetFound = false;
                        // loops through the word Indices of phraseRef[i]->getRefs()[k]
                        for(int m = 0; m < phraseRef[i]->getRefs()[k].getWordIndices().size(); m++)
                        {
                            if(targetLoc == phraseRef[i]->getRefs()[k].getWordIndices()[m])
                            {
                                targetFound = true;
                            }
                        }
                        if(!targetFound)
                        {
                            phrase->getRefs()[j].getWordIndices().erase(phrase->getRefs()[j].getWordIndices().begin() + l--);                          
                        }
                    }
                }
            }
            if(phrase->getRefs()[j].getWordIndices().size() == 0)
            {
                phrase->getRefs().erase(phrase->getRefs().begin() + j--);
            }
            if(!idFound)
            {
                phrase->getRefs().erase(phrase->getRefs().begin() +j--);
            }
        }
    }
    return phrase;
}

vector<PageLocation>* QueryProcessor::processOr(vector<string> &arg)
{
    vector<vector<PageLocation>> fullSet;
    for(int i = 0; i < arg.size(); i++)
    {
        WordRef* temp = new WordRef;
        vector<string> phraseWords;
        if(arg[i][0] == '[')
        {
            phraseWords.push_back(arg[i]);
            i++; 
            while(arg[i][arg[i].length() - 1] != ']')
            {
                phraseWords.push_back(arg[i++]);
            }
            phraseWords.push_back(arg[i]);
            temp = findPhrase(phraseWords);
        }
        else
            temp = findWord(arg[i]);
        if(temp == nullptr)
            cout << "Word: " << temp->getWord() << " not found\n";

        else
        {
            fullSet.push_back(findPages(temp));
            delete temp;
        }
    }
    trimmedSet = fullSet[0];

    bool wordExists;
    // loops through the entire fullset
    for(int i = 1; i < fullSet.size(); i++)
    {
        // loops through the subset of fullset
        for(int j = 0; j < fullSet[i].size(); j++)
        {
            wordExists = false;
            // loops through the already added words
            for(int k = 0; k < trimmedSet.size(); k++)
            {
                if(fullSet[i][j].getPageID() == trimmedSet[k].getPageID())
                {
                    wordExists = true;
                    trimmedSet[k].addTfIdf(fullSet[i][j].getTfIdf());

                    break;
                }
            }
            if(!wordExists)
                trimmedSet.push_back(fullSet[i][j]);
        }
    }
    return &trimmedSet;
}

void QueryProcessor::processAnd(vector<string> &arg)
{ 
    vector<vector<PageLocation>> fullSet;
    for(int i = 0; i < arg.size(); i++)
    {
        WordRef* temp = new WordRef;
        temp = findWord(arg[i]);
        if(temp == nullptr)
            cout << "Word: " << temp->getWord() << " not found\n";

        else
            fullSet.push_back(findPages(temp));
    }

    int k = 0;
    for(int i = 0; i < fullSet[0].size(); i++)
    {
        for(int j = 0; j < fullSet[1].size(); j++)
        {
            if(fullSet[0][i].getPageID() == fullSet[1][j].getPageID())
            {
                trimmedSet.push_back(fullSet[0][i]);
                trimmedSet[k++].addTfIdf(fullSet[1][j].getTfIdf());
            }
        }
    }
    for(int k = 0; k < trimmedSet.size(); k++)
    {
        for(int i = 2; i < fullSet.size(); i++)
        {
            bool found = false;
            for(int j = 0; j < fullSet[i].size(); j++)
            {
                if(fullSet[i][j].getPageID() == trimmedSet[k].getPageID())
                {
                    found = true;
                    trimmedSet[k].addTfIdf(fullSet[i][j].getTfIdf()); 
                }
            }
            if(!found)
                trimmedSet.erase(trimmedSet.begin() + k);
        }
    }
}

void QueryProcessor::processNot(vector<string> &arg)
{
    vector<vector<PageLocation>> fullSet;
    for(int i = 0; i < arg.size(); i++)
    {
        WordRef* temp = new WordRef;
        temp = findWord(arg[i]);
        if(temp == nullptr)
            cout << "Word: " << temp->getWord() << " not found\n";
        else
            fullSet.push_back(findPages(temp));
    }
    for(int i = 0; i < fullSet.size(); i++)
    {
        for(int j = 0; j < fullSet[i].size(); j++)
        {
            for(int k = 0; k < trimmedSet.size(); k++)
            {
                if(fullSet[i][j].getPageID() == trimmedSet[k].getPageID())
                {
                    trimmedSet.erase(trimmedSet.begin() + k);
                }
                //break;
            }
        }
    }
}

WordRef* QueryProcessor::findWord(std::string &word)
{
    return handler->searchIndex(word);
}

void QueryProcessor::stem(string &word)
{
    Porter2Stemmer::stem(word);
}

vector<PageLocation>& QueryProcessor::findPages(WordRef* ref)
{
    for(int i = 0; i < ref->getRefs().size(); i++)
    {
        calcTfIdf(ref->getRefs()[i], ref);
    }
    return ref->getRefs();
}

void QueryProcessor::printPages(vector<PageLocation> &results)
{
    sort(results.begin(), results.end());
    reverse(results.begin(), results.end());
    if(results.size() < 15)
    {
        for(int i = 0; i < results.size(); i++)
        {
            cout << i + 1 << ": \n\tid: " << results[i].getPageID() << "\n\tTF/ IDF: " << results[i].getTfIdf() << "\n";
        }
    }
    else
    {
        for(int i = 0; i < 15; i++)
        {
            cout << i + 1 << ": \n\tid: " << results[i].getPageID() << "\n\tTF/ IDF: " << results[i].getTfIdf() << "\n";
        }
    }
} 
void QueryProcessor::calcTfIdf(PageLocation& page, WordRef* ref)
{
    double tfidf = (double)page.getWordIndices().size() / (double)ref->getCorpusFreq();
    page.setTfIdf(tfidf);
}
bool operator<(const PageLocation &l, const PageLocation &r)
{
    return l.tfidf < r.tfidf;
}

vector<PageLocation>& QueryProcessor::getResults()
{
    return trimmedSet;
}

void QueryProcessor::clearResults()
{
    trimmedSet.clear();
}
