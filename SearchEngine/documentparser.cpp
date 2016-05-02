#include "documentparser.h"
#include "wordref.h"
#include "avltree.h"
#include <iostream>
#include "rapidxml.hpp"
#include <fstream>
#include <string>
#include <streambuf>
#include <vector>
#include <algorithm>
#include <sstream>
#include "myhash.h"

DocumentParser::DocumentParser()
{
}

DocumentParser::DocumentParser(string stopwordsPath)
{
    readStopWords(stopwordsPath);
}

using namespace std;


void DocumentParser::parseFile(string path, IndexInterface *data)
{
    files.emplace_back();
    XMLFile &file = files.back();
    file.setDocument(path);

    rapidxml::xml_node<> *page = file.getFirstPage();
    rapidxml::xml_node<> *elem;
    string title, id, text;

    while(page!=NULL)
    {
        //extracts the necessary imformation from the xml page
        elem = page->first_node("id");
        id = elem->value();
        elem = elem->next_sibling("revision");
        elem = elem->first_node("text");
        text = elem->value();
        page = page->next_sibling("page");
        addToMainIntex(text, id, data);
    }
}

void DocumentParser::readStopWords(string path)
{
    stopwords.clear();
    ifstream file(path);
    string word;
    while(file>>word)
    {
        stopwords.insert(word);
    }
    cout << "stopwords" << stopwords.size() << endl;
}

bool DocumentParser::isStopWord(string &word)
{
    return stopwords.find(word) != stopwords.end();
}

void DocumentParser::stem(string &word)
{
    Porter2Stemmer::stem(word);
}

//also need to remove puncutation
void DocumentParser::makeLower(string &word)
{
    transform(word.begin(), word.end(), word.begin(), ::tolower);
}

void DocumentParser::addToMainIntex(string &text, string &docId, IndexInterface *ind)
{
    //stringstream to tokenize page elements
    stringstream ss(text);
    string token = "";
    vector<pair<string,int>> tokens;
    //use pairs to tie pages to
    pair<string, int> tokPair;
    int index = 0;
    string beforeStem;
    while (ss>>token)
    {
        trimPunct(token);
        //add code to check beginning for punctuation
        if(token.size()<20 && isalpha(token[0]) && isalpha(token[token.size()-1]))
        {
            makeLower(token);
            if(!isStopWord(token))
            {
                if(indexed.find(token)==indexed.end())
                {
                    beforeStem = token;
                    stem(token);
                    //if(beforeStem!=token)
                    indexed[beforeStem] = token;
                }
                else
                {
                    token = indexed[token];
                }
                tokPair.first = token;
                tokPair.second = index;
                tokens.push_back(tokPair);
            }
        }
        ++index;
    }

    //Idea is to sort pairs of words w/indexes in order to prevent looking up the same word multiple
    //times in the data structure. It might just add too much time
    sort(tokens.begin(), tokens.end());

    size_t rightInd;
    WordRef *indWRefPtr;
    //added -1
    for(size_t leftInd=0;leftInd<tokens.size();leftInd++)
    {
        ////////////////////////////////////////////////////////////////////////////
        //gets all indicies of the word on the page
        vector<int> indicies;
        rightInd=leftInd;
        while((rightInd<tokens.size()) && (tokens.at(rightInd).first==tokens.at(leftInd).first))
        {
            indicies.push_back(tokens.at(rightInd).second);
            ++rightInd;
        }
        ////////////////////////////////////////////////////////////////////////////

        //make a WordRef to check if its already in the data structure
        WordRef tokRef;
        tokRef.setWord(tokens.at(leftInd).first);
        tokRef.insertRef(stoi(docId), indicies);

        //this block of code is used to add words to the IndexInterface, whichever type it is
        //---------------------------------------------------------------

        indWRefPtr = ind->searchVal(tokRef);

        if(indWRefPtr==nullptr)
        {
            ind->insert(tokRef);
        }
        else
        {
            indWRefPtr->insertRef(stoi(docId),indicies);
        }

        //---------------------------------------------------------------
        leftInd = rightInd;

    }
}

void DocumentParser::trimPunct(string &word)
{
    if(word[0]=='<')
    {
        size_t closing = word.find('>');
        if(closing!=string::npos)
        {
            word = word.substr(closing+1);
        }
    }
    if(word[word.size()-1]=='>')
    {
        size_t opening = word.find_last_of('<');
        if(opening!=string::npos)
        {
            word = word.substr(0,opening);
        }
    }

    size_t l,r;
    for(l=0;l<word.size() && !isalpha(word[l]);l++);
    for(r=word.size()-1;r>l && !isalpha(word[r]);r--);

    if(l!=0 || r!=word.size()-1)
        word = word.substr(l,r-l+1);

    if(word.find_first_of('<')!=string::npos || word.find_first_of('>')!=string::npos || word.find_first_of('&')!=string::npos)
        word="";
}

void DocumentParser::addFromPersistent(string path)
{
    files.emplace_back();
    XMLFile &file = files.back();
    file.setDocument(path);
}

rapidxml::xml_node<>* DocumentParser::getPage(int pageId)
{
    rapidxml::xml_node<>* node = nullptr;
    for(XMLFile &f:files)
    {
        node = f.getPage(pageId);
        if(node!=nullptr)
            return node;
    }
    return node;
}

int DocumentParser::getPagesIndexed()
{
    int total = 0;
    for(XMLFile &f:files)
    {
        total+=f.getPageCount();
    }
    return total;
}

void DocumentParser::clearFiles()
{
    files.clear();
}

vector<string> DocumentParser::getFilesAdded()
{
    vector<string> filePaths;
    for(XMLFile &f:files)
    {
        filePaths.push_back(f.getName());
    }
    return filePaths;
}
