/**
 * @file main.cpp
 * @author Sean Massung
 * @date September 2012
 *
 * An example using the Porter2Stemmer namespace.
 *
 * Words are read from the file diffs.txt
 *  (from http://snowball.tartarus.org/algorithms/english/diffs.txt)
 *  and compared against the correct output.
 */

#include "userinterface.h"
#include "pagelocation.h"
#include "indexhandler.h"
#include "wordref.h"
#include <vector>
#include <iostream>
#include <unordered_map>
#include "myhash.h"
using namespace std;

int main(int argc, char* argv[])
{

    UserInterface ui;
    ui.displayMainMenu();

    return 0;
}


