#include "documentparser.h"
#include "indexhandler.h"
#include "userinterface.h"
#include <cstdlib>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <cctype>
#include <string>
#include <limits>
#include <algorithm>

using namespace std;

UserInterface::UserInterface()
{
    processor.setHandler(indexhandler);
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
    while(!isAllCharsDigit(choice) || stoi(choice) < 0 || stoi(choice) > 2)
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
    int choiceInt = stoi(choice);

    // Execute chosen menu item
    switch(choiceInt)
    {
    case 0:
        // Write index to the persistent index file
        indexhandler.writePersistentIndex();
        indexhandler.deleteIndex();

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
    while(!isAllCharsDigit(choice) || stoi(choice) < 0 || stoi(choice) > 2)
    {
        // Print error, redisplay menu, and recieve input
        cout << "\nChoice must be in the range of 0 - 2.\n"
             << "0. Back to main menu\n"
             << "1. Add documents\n"
             << "2. Clear index\n"
             << "Choose option: ";
        cin >> choice;
        // Ignore characters after and including spaces
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    // Convert input string to int
    int choiceInt = stoi(choice);

    // Create variable to hold the path input by user
    string path;
    size_t foundPos;

    // Execute chosen menu item
    switch(choiceInt)
    {
    case 0:
        displayMainMenu();
        break;
    case 1:
        cout << "\nEnter path to new documents: ";
        getline(cin, path);

        // Repeat input until valid or cancel
        while(!ifstream(path) || find(indexhandler.getPaths().begin(), indexhandler.getPaths().end(), path) != indexhandler.getPaths().end())
        {
            if(!ifstream(path))
                cout << "Invalid path.\nEnter path to new documents (\"0\" to return to Maintenance Mode): ";
            else
                cout << "Path is already added.\nEnter path to new documents (\"0\" to return to Maintenance Mode): ";

            // Reenter input
            getline(cin, path);

            // Cancel if input is sentinal value
            if(path == "0")
                enterMaintenanceMode();
        }

        // Add path to vector of all paths and
        // vector of new paths to be added to persistent index
        indexhandler.addNewPath(path);
        indexhandler.addPath(path);
        break;
    case 2:
        indexhandler.clearIndex();
        cout << "\nIndex cleared.\n";
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
   while(!isAllCharsDigit(choice) || stoi(choice) < 0 || stoi(choice) > 2)
    {
        // Print error, redisplay menu, and recieve input
        cout << "\nChoice must be in the range of 0 - 2.\n"
             << "0. Back to main menu\n"
             << "1. Load index into AVL tree\n"
             << "2. Load index into hash table\n"
             << "Choose option: ";
        cin >> choice;
        // Ignore characters after and including spaces
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    // Convert input string to int
    int choiceInt = stoi(choice);

    // Execute chosen menu item
    switch(choiceInt)
    {
    case 0:
        displayMainMenu();
        break;
    case 1:
        indexhandler.setIndexType(choiceInt);
        break;
    case 2:
        indexhandler.setIndexType(choiceInt);
        break;
    default:
        cerr << "Error: Invalid choice in interactive mode\n";
        exit(EXIT_FAILURE);
    }

    if(indexhandler.getNewPaths().empty())
    {
        indexhandler.clearTop50Words();
        indexhandler.deleteIndex();
    }

    // Create index using the index type
    indexhandler.createIndex();

    // Read persistent index into index
    if(ifstream(indexhandler.getFileName()))
    {
        // If file already exists then read the persistent index
        indexhandler.readPersistentIndex();

        displayQueryMenu();
    }
    // If there are documents staged to add then add them to index and persistent index
    else if(!indexhandler.getNewPaths().empty())
    {
        // Index all of the new paths
        indexhandler.indexPaths(indexhandler.getNewPaths());
        displayQueryMenu();
    }
    // Index is empty and no new documents are staged to be added
    else if(indexhandler.getPaths().empty())
    {
         cout << "\nYou must add documents before loading index\n";
         enterInteractiveMode();
    }
    else if(!indexhandler.getPaths().empty())
    {
        // Index all of the new paths
        indexhandler.indexPaths(indexhandler.getPaths());
        displayQueryMenu();
    }
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
    while(!isAllCharsDigit(choice) || stoi(choice) < 0 || stoi(choice) > 2)
    {
        // Print error, redisplay menu, and recieve input
        cout << "\nChoice must be in the range of 0 - 2.\n"
             << "0. Back to interactive mode menu\n"
             << "1. Enter boolean query\n"
             << "2. Get search engine statistics\n"
             << "Choose option: ";
        cin >> choice;
        // Ignore characters after and including spaces
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    // Convert input string to int
    int choiceInt = stoi(choice);

    // Create variable to store query
    string query;

    // Execute chosen menu item
    switch(choiceInt)
    {
    case 0:
        enterInteractiveMode();
        break;
    case 1:
        cout << "\nEnter query: ";
        getline(cin, query);

        processor.processQuery(query);

        for(int i = 0; i < (processor.getResults().size() < 15 ? processor.getResults().size() : 15); i++)
        {
            cout << i + 1 << "\n\tid: " << processor.getResults()[i].getPageID() << "\n\tTF/IDF: " << processor.getResults()[i].getTfIdf() << "\n";
        }

        processor.clearResults();
        break;
    case 2:
    {
        indexhandler.calculateStats();

        cout << "\nSEARCH ENGINE STATISTICS:\n"
             << "\nTotal number of pages indexed: " << indexhandler.getNumPages()
             << "\nTotal number of words indexed: " << indexhandler.getNumWords()
             << "\nTop 50 most frequent words: \n";

        // Create the vector of the top 50 word-frequency pairs
        std::vector<std::pair<std::string,int>> top50Words = indexhandler.getTop50Words();

        // Print the column titles
        cout << "    " << setw(25) << left << "Word" << "Frequency\n";
        // Print the top 50 list
        for(size_t n=0; n<top50Words.size(); n++)
        {
            cout << setw(2) << right << n+1 << ". " << setw(25) << left << top50Words[n].first << top50Words[n].second << "\n";
        }
        break;
    }
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
    for(size_t i=0; i<word.length(); i++)
    {
        // If any character is a letter then return false
        if(isalpha(word[i]))
            return false;
    }
    // If no characters are letters then return true
    return true;
}
