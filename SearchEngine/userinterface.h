/*
 * File: Userinterface.h
 * Owner: Kellen Schmidt
 * Update History:
 *
 */

#ifndef USERINTERFACE_H
#define USERINTERFACE_H

#include <string>

class UserInterface
{
public:
    UserInterface();
    void displayMainMenu();

<<<<<<< HEAD

=======
private:
    void printTitle();
    void enterMaintenanceMode();
    void enterInteractiveMode();
    void displayQueryMenu();
    bool isAllCharsDigit(std::string);
>>>>>>> f3216982b8afeb792731f1330d8dc156e1ac887b
};

#endif // USERINTERFACE_H
