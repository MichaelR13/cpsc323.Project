// This lexer will be built using 2 Finite State Machines:
// 1. FSM for Identifiers
// 2. FSM for Integers and Real Numbers

// This program will ask the user for a file name and then read/tokenize the file
// and output the tokens to the console.

// BASE THIS PROGRAM OFF OF sample.cpp

#include <iostream>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string>
#include <string.h>

using namespace std;

// function that asks the user for a file name and opens the file
void openFiles()
{
    string inFile;
    cout << "Enter the name of the file you want to open: ";
    cin >> inFile;
    ifstream fin(inFile);
    ofstream fout("output.txt");
}

