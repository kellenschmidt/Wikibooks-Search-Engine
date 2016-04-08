#include "userinterface.h"
#include <cstdlib>
#include <iostream>
#include <cctype>
#include <string>
#include <limits>

using namespace std;

UserInterface::UserInterface()
{

}

void UserInterface::printTitle()
{
    cout << "███████╗███████╗ █████╗ ██████╗  ██████╗██╗  ██╗    ███████╗███╗   ██╗ ██████╗ ██╗███╗   ██╗███████╗\n"
         << "██╔════╝██╔════╝██╔══██╗██╔══██╗██╔════╝██║  ██║    ██╔════╝████╗  ██║██╔════╝ ██║████╗  ██║██╔════╝\n"
         << "███████╗█████╗  ███████║██████╔╝██║     ███████║    █████╗  ██╔██╗ ██║██║  ███╗██║██╔██╗ ██║█████╗  \n"
         << "╚════██║██╔══╝  ██╔══██║██╔══██╗██║     ██╔══██║    ██╔══╝  ██║╚██╗██║██║   ██║██║██║╚██╗██║██╔══╝  \n"
         << "███████║███████╗██║  ██║██║  ██║╚██████╗██║  ██║    ███████╗██║ ╚████║╚██████╔╝██║██║ ╚████║███████╗\n"
         << "╚══════╝╚══════╝╚═╝  ╚═╝╚═╝  ╚═╝ ╚═════╝╚═╝  ╚═╝    ╚══════╝╚═╝  ╚═══╝ ╚═════╝ ╚═╝╚═╝  ╚═══╝╚══════╝\n\n";
}

void UserInterface::displayMainMenu()
{
    // Only display the fancy title the first time
    static int dispOneTime = 0;
    if(dispOneTime++ == 0)
        printTitle();
    else
        cout << "\nMAIN MENU\n\n";

    // Display menu and recieve input
    cout << "0. Exit\n"
         << "1. Maintenance Mode\n"
         << "2. Interactive Mode\n"
         << "Choose mode: ";

    string choice;
    cin >> choice;
    // Ignore characters after and including spaces
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    // Loop until input is all digits and within the range
    while(!isAllCharsDigit(choice) || atoi(choice.c_str()) < 0 || atoi(choice.c_str()) > 2)
    {
        // Print error, redisplay menu, and recieve input
        cout << "\nChoice must be in the range of 0 - 2.\n"
             << "0. Exit\n"
             << "1. Maintenance Mode\n"
             << "2. Interactive Mode\n"
             << "Choose mode: ";
        cin >> choice;
        // Ignore characters after and including spaces
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    // Convert input string to int
    int choiceInt = atoi(choice.c_str());

    // Execute chosen menu item
    switch(choiceInt)
    {
    case 0:
        exit(EXIT_SUCCESS);
        break;
    case 1:
        enterMaintenanceMode();
        break;
    case 2:
        enterInteractiveMode();
        break;
    default:
        cerr << "Error: Invalid main menu mode choice\n";
        exit(EXIT_FAILURE);
    }
}

void UserInterface::enterMaintenanceMode()
{
    cout << "\nMAINTENANCE MODE\n\n";

    // Display menu and recieve input
    cout << "0. Back to main menu\n"
         << "1. Add documents\n"
         << "2. Clear index\n"
         << "Choose option: ";

    string choice;
    cin >> choice;
    // Ignore characters after and including spaces
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    // Loop until input is all digits and within the range
    while(!isAllCharsDigit(choice) || atoi(choice.c_str()) < 0 || atoi(choice.c_str()) > 2)
    {
        // Print error, redisplay menu, and recieve input
        cout << "\nChoice must be in the range of 0 - 2.\n"
             << "0. Back to main menu\n"
             << "1. Add documents\n"
             << "2. Clear index\n"
             << "Choose mode: ";
        cin >> choice;
        // Ignore characters after and including spaces
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    // Convert input string to int
    int choiceInt = atoi(choice.c_str());

    // Execute chosen menu item
    switch(choiceInt)
    {
    case 0:
        displayMainMenu();
        break;
    case 1:
        cout << "\nThis is where new documents will be added\n";
        break;
    case 2:
        cout << "\nThis is where the index will be cleared\n";
        break;
    default:
        cerr << "Error: Invalid choice in maintenance mode\n";
        exit(EXIT_FAILURE);
    }

    // Automatically redisplay menu after executing command
    enterMaintenanceMode();
}

void UserInterface::enterInteractiveMode()
{
    cout << "\nINTERACTIVE MODE\n\n";

    /// TODO: First check if persistent index exists
    /// If it doesn't exit, then stop and display error
    /// Then prompt to go to maintenance mode

    // Display menu and recieve input
    cout << "0. Back to main menu\n"
         << "1. Load index into AVL tree\n"
         << "2. Load index into hash table\n"
         << "Choose option: ";

    string choice;
    cin >> choice;
    // Ignore characters after and including spaces
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    // Loop until input is all digits and within the range
    while(!isAllCharsDigit(choice) || atoi(choice.c_str()) < 0 || atoi(choice.c_str()) > 2)
    {
        // Print error, redisplay menu, and recieve input
        cout << "\nChoice must be in the range of 0 - 2.\n"
             << "0. Back to main menu\n"
             << "1. Load index into AVL tree\n"
             << "2. Load index into hash table\n"
             << "Choose mode: ";
        cin >> choice;
        // Ignore characters after and including spaces
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    // Convert input string to int
    int choiceInt = atoi(choice.c_str());

    // Execute chosen menu item
    switch(choiceInt)
    {
    case 0:
        displayMainMenu();
        break;
    case 1:
        cout << "\nThis is where index will be loaded into AVL tree\n";
        break;
    case 2:
        cout << "\nThis is where index will be loaded into hash table\n";
        break;
    default:
        cerr << "Error: Invalid choice in interactive mode\n";
        exit(EXIT_FAILURE);
    }

    // Automatically redisplay menu after executing command
    displayQueryMenu();
}

void UserInterface::displayQueryMenu()
{
    cout << "\nSEARCH QUERY MENU\n\n";

    // Display menu and recieve input
    cout << "0. Back to interactive mode menu\n"
         << "1. Enter boolean query\n"
         << "2. Get search engine statistics\n"
         << "Choose option: ";

    string choice;
    cin >> choice;
    // Ignore characters after and including spaces
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    // Loop until input is all digits and within the range
    while(!isAllCharsDigit(choice) || atoi(choice.c_str()) < 0 || atoi(choice.c_str()) > 2)
    {
        // Print error, redisplay menu, and recieve input
        cout << "\nChoice must be in the range of 0 - 2.\n"
             << "0. Back to interactive mode menu\n"
             << "1. Enter boolean query\n"
             << "2. Get search engine statistics\n"
             << "Choose mode: ";
        cin >> choice;
        // Ignore characters after and including spaces
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    // Convert input string to int
    int choiceInt = atoi(choice.c_str());

    // Execute chosen menu item
    switch(choiceInt)
    {
    case 0:
        enterInteractiveMode();
        break;
    case 1:
        // TODO: Call some function to recieve process and output results of boolean query
        cout << "\nThis is where you call fancy function to recieve and process search\n";
        break;
    case 2:
        cout << "\nSEARCH ENGINE STATISTICS:\n"
             << "\nTotal number of pages indexed: "
             << "\nTotal number of words indexed: "
             << "\nTop 50 most frequent words: \n";
        break;
    default:
        cerr << "Error: Invalid choice in boolean query menu mode\n";
        exit(EXIT_FAILURE);
    }

    // Automatically redisplay menu after executing command
    displayQueryMenu();
}

bool UserInterface::isAllCharsDigit(string word)
{
    // Loop through each character in the string
    for(int i=0; i<word.length(); i++)
    {
        // If any character is a letter then return false
        if(isalpha(word[i]))
            return false;
        if(word[i] == ' ')
        {
            word.erase(i, 1);
            i--;
        }
    }
    // If no characters are letters then return true
    return true;
}
