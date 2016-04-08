#ifndef USERINTERFACE_H
#define USERINTERFACE_H

#include <string>

class UserInterface
{
public:
    UserInterface();
    void displayMainMenu();

private:
    void printTitle();
    void enterMaintenanceMode();
    void enterInteractiveMode();
    void displayQueryMenu();
    bool isAllCharsDigit(std::string);
};

#endif // USERINTERFACE_H
