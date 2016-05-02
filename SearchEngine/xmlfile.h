/* File: xmlfile.h
 * Name: Lucas Hansen
 *
 * Update History:
 * April 17, 2016 - Created file
 * April 17, 2016 - Implemented XML DOM generation in this calss wather than DocumentParser
 * April 24, 2016 - Implemented ability to get a wikibooks page pointer by passing an int
 */

#ifndef XMLFILE_H
#define XMLFILE_H
#include "rapidxml.hpp"
#include <vector>
#include <string>

class XMLFile
{
public:
    XMLFile();
    XMLFile(std::string fPath);
    XMLFile(const XMLFile &other);
    //~XMLFile();
    void setDocument(std::string fPath);
    std::string getName();
    rapidxml::xml_node<>* getFirstPage();
    int getPageCount();

    bool containsPage(int pageNum);
    rapidxml::xml_node<>* getPage(int pageId);


private:
    std::string name;
    rapidxml::xml_document<> document;
    std::string xmlFileString;
    std::pair<int,int> pageRange;
    int pageCount;

};

#endif // XMLFILE_H
