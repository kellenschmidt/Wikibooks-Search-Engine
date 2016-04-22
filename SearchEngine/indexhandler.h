#ifndef INDEXHANDLER_H
#define INDEXHANDLER_H

#include "indexinterface.h"
#include "wordref.h"
#include <fstream>
#include <vector>
#include <string>

class IndexHandler
{
private:
    IndexInterface *index;
    std::vector<std::string> filePaths;
    std::vector<std::string> newPaths;
    int indexType;
    std::string fileName;
    std::fstream persistentIndexFile;
    int numWords;
    int numPages;
    std::vector<std::pair<std::string,int>> top50Words;

public:
    IndexHandler();
    void indexPaths(const std::vector<std::string>&);
    void setIndexType(int);
    int getIndexType();
    int getNumWords();
    int getNumPages();
    std::vector<std::pair<std::string,int>> getTop50Words();
    std::string getFileName();
    std::vector<std::string>& getPaths();
    std::vector<std::string>& getNewPaths();
    void addPath(std::string);
    void addNewPath(std::string);
    void clearIndex();
    void createIndex();
    void writePersistentIndex();
    void readPersistentIndex();
    WordRef* searchIndex(std::string&);
};

#endif // INDEXHANDLER_H
