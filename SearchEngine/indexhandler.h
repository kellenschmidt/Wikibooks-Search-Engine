#ifndef INDEXHANDLER_H
#define INDEXHANDLER_H

#include "indexinterface.h"
#include <fstream>
#include <vector>
#include <string>

class IndexHandler
{
private:
    IndexInterface *index;
    std::vector<std::string> filePaths;
    // 1 = AVLTree, 2 = HashTable
    int indexType;
    std::string fileName;
    std::fstream persistentIndexFile;

public:
    IndexHandler();
    void indexPaths();
    void setIndexType(int);
    int getIndexType();
    void addPath(std::string);
    void addWord(std::string, int, int);
    void createIndex();
    void writePersistentIndex();
    void readPersistentIndex();
};

#endif // INDEXHANDLER_H
