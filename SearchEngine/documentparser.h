#ifndef DOCUMENTPARSER_H
#define DOCUMENTPARSER_H
#include <string>
#include "porter2_stemmer.h"
#include "rapidxml.hpp"
#include <unordered_set>
#include "avltree.h"
using namespace std;
class DocumentParser
{
private:
    void addToMainIntex(string &text, string &docId, AvlTree<string> *tree);

    void addToFileIndex(string &path, string &docId);
    void readStopWords(string path);
    unordered_set<string> stopwords;

public:
    DocumentParser();
    DocumentParser(string stopwordsPath);
    //, IndexInterface &index
    void parseFile(string path, AvlTree<string> *tree);
    bool isStopWord(string &word);
    void stem(string &word);
    void makeLower(string &word);



};

#endif // DOCUMENTPARSER_H
