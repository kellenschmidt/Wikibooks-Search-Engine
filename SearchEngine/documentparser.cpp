/* Lucas Hansen
 * Currently, the document parser only works with Luke's main.cpp
 */
#include "documentparser.h"
//#include "indexinterface.h"
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
DocumentParser::DocumentParser(string stopwordsPath)
{
    readStopWords(stopwordsPath);
}

using namespace std;
//, IndexInterface &index
void DocumentParser::parseFile(string path, IndexInterface *tree)
{
    ifstream xmlFile(path);
    //add error checking
    string xmlFileString;

    xmlFile.seekg(0, ios::end);
    xmlFileString.reserve(xmlFile.tellg());
    xmlFile.seekg(0, ios::beg);

    xmlFileString.assign((istreambuf_iterator<char>(xmlFile)), istreambuf_iterator<char>());
    rapidxml::xml_document<> doc;
    //rapidxml::parse_non_destructive|rapidxml::parse_no_data_nodes
    doc.parse<rapidxml::parse_no_data_nodes>(&xmlFileString[0]);
    rapidxml::xml_node<> *page = doc.first_node("mediawiki")->first_node("page");
    rapidxml::xml_node<> *elem;
    string title, id, text;
    cout << "read into DOM tree" << endl;

    while(page!=NULL)
    {
        //extracts the necessary imformation from the xml page
        elem = page->first_node("title");
        title = elem->value();
        elem = elem->next_sibling("id"); //need to put something here
        id = elem->value();
        elem = elem->next_sibling("revision");
        elem = elem->first_node("text");
        text = elem->value();
        page = page->next_sibling("page");

        addToMainIntex(text, id, tree);
        //will need to add the document number and file path to another data structure for lookup
        //add possibly another one for user/editor name, etc..
        //addToFileIndex();
    }

    xmlFile.close();
    doc.clear();
}

void DocumentParser::readStopWords(string path)
{
    ifstream file(path);
    string word;
    while(file>>word)
    {
        stopwords.insert(word);
    }
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

void DocumentParser::addToMainIntex(string &text, string &docId, IndexInterface *tree)
{
    //stringstream to tokenize page elements
    stringstream ss(text);
    string token;
    vector<pair<string,int>> tokens;
    //use pairs to tie pages to
    pair<string, int> tokPair;
    int index = 0;
    string beforeStem;
    while (ss>>token)
    {
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

        //This block of code adds all the words to the std::unordered_map, called test, in the header file
        //--------------------------------------------------------------
        /*
        if(test.find(tokRef.getWord())==test.end())
        {
            test[tokRef.getWord()] = tokRef;
        }
        else
        {
            test[tokRef.getWord()].insertRef(stoi(docId),indicies);
        }
        */
        //---------------------------------------------------------------


        //this block of code is used to add words to the IndexInterface, whichever type it is
        //hashtable is not yet implemented fully
        //---------------------------------------------------------------

        indWRefPtr = tree->searchVal(tokRef);

        if(indWRefPtr==nullptr)
        {
            tree->insert(tokRef);
        }
        else
        {
            indWRefPtr->insertRef(stoi(docId),indicies);
        }

        //---------------------------------------------------------------



        leftInd = rightInd;
    }
}
