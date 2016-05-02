#include "xmlfile.h"
#include "rapidxml.hpp"
#include <fstream>
#include <vector>
#include <iostream>

using namespace std;

XMLFile::XMLFile()
{
    //document = new rapidxml::xml_document<>;
    pageCount = 0;
    cout << "XMLFile default" << endl;
}

XMLFile::XMLFile(std::string fPath)
{
    //document = new rapidxml::xml_document<>;
    pageCount = 0;
    setDocument(fPath);
    cout << "XMLFile string constr" << endl;
}

void XMLFile::setDocument(string fPath)
{
    name = fPath;
    //document.clear();
    ifstream xmlFile(fPath);

    xmlFile.seekg(0, ios::end);
    xmlFileString.reserve(xmlFile.tellg());
    xmlFile.seekg(0, ios::beg);

    xmlFileString.assign((istreambuf_iterator<char>(xmlFile)), istreambuf_iterator<char>());
    //rapidxml::parse_non_destructive|rapidxml::parse_no_data_nodes
    document.parse<0>(&xmlFileString[0]);
    //document.parse<rapidxml::parse_no_data_nodes>(&xmlFileString[0]);
    cout << "parsed" << endl;

    //get range of page IDs
    rapidxml::xml_node<> *page = document.first_node("mediawiki")->first_node("page");
    pageRange.first = stoi(page->first_node("id")->value());
    page = document.first_node("mediawiki")->last_node("page");
    pageRange.second = stoi(page->first_node("id")->value());


    page = document.first_node("mediawiki")->first_node("page");
    while(page)
    {
        pageCount++;
        page = page->next_sibling("page");
    }
}

bool XMLFile::containsPage(int pageNum)
{
    return (pageNum>=pageRange.first) && (pageNum<=pageRange.second);
}

rapidxml::xml_node<>* XMLFile::getPage(int pageId)
{
    if(containsPage(pageId))
    {
        rapidxml::xml_node<> *page = document.first_node("mediawiki")->first_node("page");
        while(stoi(page->first_node("id")->value())!=pageId)
            page = page->next_sibling("page");
        return page;
    }
    else
    {
        return nullptr;
    }
}

rapidxml::xml_node<>* XMLFile::getFirstPage()
{
    return (document.first_node("mediawiki")->first_node("page"));
}

XMLFile::XMLFile(const XMLFile &other)
{
    name = other.name;
    //document = other.document;

}

string XMLFile::getName()
{
    return name;
}

int XMLFile::getPageCount()
{
    return pageCount;
}
