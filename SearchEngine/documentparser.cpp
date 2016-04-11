#include "documentparser.h"
#include "indexinterface.h"
#include "wordref.h"
#include "rapidxml.hpp"
#include "indexhandler.h"
#include <iostream>

using namespace std;

DocumentParser::DocumentParser()
{

}

void DocumentParser::parseFile(string pathToIndex)
{
    rapidxml::xml_document<> doc;
    // Might need to add .c_str() if pare function has char* parameter
    doc.parse(pathToIndex);
    rapidxml::xml_node<> *page = doc->first_node("mediawiki")->first_node("page");
    rapidxml::xml_node<> *elem;
    while(page != nullptr)
    {
        elem = page->first_node("title");
        title = elem->value();
        elem = elem->next_sibling("id");
        id = elem->value();
        // totally unfinished
    }


}
