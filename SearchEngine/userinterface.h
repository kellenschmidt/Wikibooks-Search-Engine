/*
 * File: Userinterface.h
 * Name: Kellen Schmidt
 * Update History:
 * 4/5/16 - Created file and class
 * 4/11/16 - Finished basic navigation of menus
 * 4/16/16 - Updated to work with query processor
 * 4/30/16 - Error handling and beautification
 */

#ifndef USERINTERFACE_H
#define USERINTERFACE_H

#include "indexhandler.h"
#include <string>
#include "queryprocessor.h"

class UserInterface
{
public:
    // Set defualt values
    UserInterface();

    // Display the first menu
    void displayMainMenu();

private:
    IndexHandler indexhandler;
    QueryProcessor processor;
    void printTitle();
    void enterMaintenanceMode();
    void enterInteractiveMode();
    void displayQueryMenu();
    bool isAllCharsDigit(std::string);
};

#endif // USERINTERFACE_H
