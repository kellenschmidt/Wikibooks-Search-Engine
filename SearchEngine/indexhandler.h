#ifndef INDEXHANDLER_H
#define INDEXHANDLER_H

///#include "indexinterface.h"
#include "wordref.h"
#include <fstream>
#include <vector>
#include <string>

class IndexHandler
{
private:
    ///IndexInterface *index;
    std::vector<std::string> filePaths;
    std::vector<std::string> newPaths;
    // 1 = AVLTree, 2 = HashTable
    int indexType;
    std::string fileName;
    std::fstream persistentIndexFile;

public:
    IndexHandler();
    std::vector<WordRef> indexPaths(const std::vector<std::string>&);
    void setIndexType(int);
    int getIndexType();
    std::vector<std::string>& getPaths();
    std::vector<std::string>& getNewPaths();
    void addPath(std::string);
    void addNewPath(std::string);
    void clearPaths();
    void createIndex();
    void writePersistentIndex(const std::vector<WordRef>&);
    void readPersistentIndex();
};

#endif // INDEXHANDLER_H
