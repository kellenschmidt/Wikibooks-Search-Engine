#ifndef DOCUMENTPARSER_H
#define DOCUMENTPARSER_H
#include <string>
#include "porter2_stemmer.h"
#include "rapidxml.hpp"
#include <unordered_set>
#include <unordered_map>
#include "avltree.h"
#include "wordref.h"
using namespace std;
class DocumentParser
{
private:
    void addToMainIntex(string &text, string &docId, IndexInterface *tree);
    void addToFileIndex(string &path, string &docId);
    void readStopWords(string path);
    unordered_set<string> stopwords;
    unordered_map<string,string> indexed;


public:
    DocumentParser();
    DocumentParser(string stopwordsPath);
    void parseFile(string path, IndexInterface *tree);
    bool isStopWord(string &word);
    void stem(string &word);
    void makeLower(string &word);

};

#endif // DOCUMENTPARSER_H
