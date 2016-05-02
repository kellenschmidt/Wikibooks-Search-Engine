/* File: documentparser.h
 * Name: Lucas Hansen
 *
 * Update History:
 * April 5, 2016 - Created file
 * April 8, 2016 - Implemented separaetion of each page in XML file into tokens
 * April 11, 2016 - Words are inserted into WordRefs, capturing necessary data
 * April 14, 2016 - Efficiency update, use unordered set to check for stopwords
 * April 21, 2016 - Stripping words of xml tags and innoring words with ampersands
 */

#ifndef DOCUMENTPARSER_H
#define DOCUMENTPARSER_H
#include <string>
#include "porter2_stemmer.h"
#include "rapidxml.hpp"
#include <unordered_set>
#include <unordered_map>
#include "avltree.h"
#include "wordref.h"
#include "xmlfile.h"
#include <list>
using namespace std;
class DocumentParser
{
private:
    void addToMainIntex(string &text, string &docId, IndexInterface *tree);
    void addToFileIndex(string &path, string &docId);
    //efficiently used to check if words on the file are stopwords
    unordered_set<string> stopwords;
    //avoid re-stemming words by storing chandes in this map
    unordered_map<string,string> indexed;
    //maintains each xml file in memory for easy accessing
    list<XMLFile> files;


public:
    DocumentParser();
    //reads in stopword file
    DocumentParser(string stopwordsPath);
    //loads stopwords into unordered set to be used during parsing
    void readStopWords(string path);
    //reads XML file into memory (used for searching) without parsing through each individual file
    void addFromPersistent(string path);
    //parses file from the given path into IndexInterface*, adds to list of XMLFiles
    void parseFile(string path, IndexInterface *tree);
    //uses unordered set to check if word is in the stopwords file (see contructor)
    bool isStopWord(string &word);
    //wrapper for porter2stemmer functionality
    void stem(string &word);
    //uses std::algorithm to convert all characters to lowercase
    void makeLower(string &word);
    //trims html tags from the beginning and end of strings, as well as other punctuation
    //does not account for punctuation between alpha characters
    void trimPunct(string &word);
    //returns pointer to xml_node with the givenPageId, no matter what document the page resides in
    //returns nullptr if not found
    rapidxml::xml_node<>* getPage(int pageId);
    //gets count of pages added to index (or that were contained in presistent index)
    //this statictic is based on the range of all the documents in each file, the program deos not
    //count each individual one
    int getPagesIndexed();
    //deletes XMLFiles from memory
    void clearFiles();
    //gets all files that have been added from persistent index or from input
    vector<string> getFilesAdded();



};

#endif // DOCUMENTPARSER_H
