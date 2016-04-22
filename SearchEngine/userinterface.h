/*
 * File: Userinterface.h
 * Owner: Kellen Schmidt
 * Update History:
 *
 */

#ifndef USERINTERFACE_H
#define USERINTERFACE_H

#include "indexhandler.h"
#include <string>
#include "queryprocessor.h"

class UserInterface
{
public:
    UserInterface();
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
