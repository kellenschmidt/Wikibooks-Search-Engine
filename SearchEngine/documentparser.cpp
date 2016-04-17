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

DocumentParser::DocumentParser(string stopwordsPath)
{
    readStopWords(stopwordsPath);
}

using namespace std;
//, IndexInterface &index
void DocumentParser::parseFile(string path, AvlTree<string> *tree, vector<WordRef> &persist)
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

void DocumentParser::addToMainIntex(string &text, string &docId, AvlTree<string> *tree)
{
    //stringstream to tokenize page elements
    stringstream ss(text);
    string token;
    vector<pair<string,int>> tokens;
    //use pairs to tie pages to
    pair<string, int> tokPair;
    int index = 0;
    while (ss>>token)
    {
        makeLower(token);
        if((all_of(token.begin(),token.end(),::isalpha)))
        {
            if(!isStopWord(token))
            {
                stem(token);
                tokPair.first = token;
                tokPair.second = index;
                tokens.push_back(tokPair);
            }
        }
        ++index;
    }
    //Tyler's idea was to sort pairs of words w/indexes in order to prevent looking up the same word multiple
    //times in the data structure. It might just add too much time
    std::sort(tokens.begin(), tokens.end(), [](const pair<string,int> &left, const pair<string,int> &right) {
        return left.first < right.first;
    });

    int rightInd;
    //allocate a wordref here
    WordRef ref;
    for(int leftInd=0;leftInd<tokens.size();++leftInd)
    {
        //TODO: add token to wordref
        while(rightInd+1<tokens.size() && tokens.at(rightInd+1)==tokens.at(leftInd))
        {
            //TODO: add token's index on page
            ++rightInd;
        }

        //add token to tree (if word exists in tree, append the indexed to it
        //^maybe we should check to see if its in the tree already??

    }

}
