#ifndef INDEXHANDLER_H
#define INDEXHANDLER_H

#include <vector>
#include <string>

class IndexHandler
{
private:
    std::vector<std::string> filePaths;
    // 1 = AVLTree, 2 = HashTable
    int indexType;
public:
    IndexHandler();
    void indexPaths();
    void setIndexType(int);
    int getIndexType();
    void addPath(std::string);
    void createIndex();
};

#endif // INDEXHANDLER_H
