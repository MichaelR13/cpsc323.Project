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

// FSM for integers and real numbers
string intRealFSM(char num) {
    // There will be 4 states: 1 - Integer, 2 - Real, 3 - Error, 4 - End
    int fsmIntReal[5][3] = {
        /*Initial State 0*/ {1, 3, 3},
        /*State 1*/         {1, 2, 3},
        /*State 2*/         {2, 3, 3},
        /*State 3*/         {3, 3, 3},
        /*State 4*/         {4, 4, 4}
    };

    // Track position in FSM
    int pos = 1;

    // Hold the numbers in an array
    char arr[100];
    arr[0] = num;   // Put the first number in the array
    int i = 1;
    char charPlusOne;

    // Loop through the file until the end of the file
    while (charPlusOne = fin.peek())    // fin.peek() will preview the next character in the file 
    {
        if (isDigit(charPlusOne))
        {

        }

        else if (charPlusOne == '.')
        {

        }

        else
        {

        }

        if (pos == 3)
        {
            // Error
        }

        else if (pos == 4)
        {
            // End
        }

        else
        {
            // Continue
        }

        fin.get();  // fin.get() will get the next character in the file
    }
    return arr;
}

string identifierFSM(char letter) 
{

}

string isKeyword(char arr[])    // this function will check if the identifier is a keyword
{
    string keywords[11] = { "if", "then", "else", "end", "repeat", "until", "read", "write", "while", "do", "endwhile" };
    int i = 0;  // counter
    while (i < 11)
    {
        if (strcmp(arr, keywords[i]) == 0)
        {
            return keywords[i];
        }
        i++;
    }
    return "Not a keyword";
}

void lexer()
{

}

int main()
{

}