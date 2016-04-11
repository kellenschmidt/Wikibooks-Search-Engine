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

class UserInterface
{
public:
    UserInterface();
    void displayMainMenu();

private:
    IndexHandler indexhandler;
    void printTitle();
    void enterMaintenanceMode();
    void enterInteractiveMode();
    void displayQueryMenu();
    bool isAllCharsDigit(std::string);
};

#endif // USERINTERFACE_H
