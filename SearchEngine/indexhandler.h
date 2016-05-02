/*
 * File: indexhandler.h
 * Name: Kellen Schmidt
 * Update history:
 * 4/5/16 - File and class created
 * 4/10/16 - File parsing is implemented
 * 4/20/16 - Peristent index is inplemented
 * 4/25/16 - Search engine statistics is implemented
 */

#ifndef INDEXHANDLER_H
#define INDEXHANDLER_H

#include "indexinterface.h"
#include "documentparser.h"
#include "wordref.h"
#include <fstream>
#include <vector>
#include <string>

class IndexHandler
{
private:
    IndexInterface *index;
    DocumentParser dp;
    std::vector<std::string> filePaths;
    std::vector<std::string> newPaths;
    int indexType;
    std::string fileName;
    std::fstream persistentIndexFile;
    int numWords;
    int numPages;
    std::vector<std::pair<std::string,int>> top50Words;

public:
    // Set default values
    IndexHandler();

    // Parse all of the files in the vector of strings
    void indexPaths(const std::vector<std::string>&);

    // Set index type, 1 = AvlTree, 2 = Hash table
    void setIndexType(int);

    // Return number of words indexed
    int getNumWords();

    // Return number of pages indexed
    int getNumPages();

    // Return vector of top 50 most frequent words
    // first element of pair is the word, second is the frequency
    std::vector<std::pair<std::string,int>> getTop50Words();

    // Return the persistent index file name
    std::string getFileName();

    // Return the vector of paths that have been parsed
    std::vector<std::string>& getPaths();

    // Return the vector of paths that are yet to be parsed
    std::vector<std::string>& getNewPaths();

    // Add a path that has been parsed
    void addPath(std::string);

    // Add a path that is yet to be parsed
    void addNewPath(std::string);

    // Clear the vector of the top 50 words
    void clearTop50Words();

    // Clear everything associated with the index
    // Reset statistics, delete persistent index, clear paths
    void clearIndex();

    // Delete index from memory and reset page/word stats
    void deleteIndex();

    // Create the index as either an AvlTree or Hash table based on indexType
    void createIndex();

    // Calculate number of pages, number of words, and 50 most frequent words
    void calculateStats();

    // Open persistent index file and write contents of index to file
    void writePersistentIndex();

    // Read contents of persistent index file into index
    void readPersistentIndex();

    // Return a pointer to the wordRef in the index where the search word is found
    WordRef* searchIndex(std::string&);

    // Return the document parser
    DocumentParser& parser();
};

#endif // INDEXHANDLER_H
