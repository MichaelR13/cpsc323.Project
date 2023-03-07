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
        /*0*/               {1, 3, 3},
        /*1*/               {1, 2, 3},
        /*2*/               {2, 3, 3},
        /*3*/               {3, 3, 3},
        /*4*/               {4, 4, 4}
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
            pos = fsmIntReal[pos][0];
        }

        else if (charPlusOne == '.')
        {
            pos = fsmIntReal[pos][1];
        }

        else
        {
            pos = fsmIntReal[pos][2];
        }

        if (pos == 3)
        {
            arr[i] = '\0';
            break;
        }

        else if (pos == 4)
        {
            arr[i] = '\0';
            break;
        }

        else
        {
            arr[i++] = charPlusOne;
        }

        fin.get();  // fin.get() will get the next character in the file
    }
    return arr;
}

string identifierFSM(char letter) {
    // There will be 4 states: 1 - Identifier, 2 - Error, 3 - End
    int fsmIdentifier[4][2] = {
        /*0*/               {1, 2},
        /*1*/               {1, 3},
        /*2*/               {2, 2},
        /*3*/               {3, 3}
    };

    // Track position in FSM
    int pos = 1;

    // Hold the letters in an array
    char arr[100];
    arr[0] = letter;    // Put the first letter in the array
    int i = 1;
    char charPlusOne;

    // Loop through the file until the end of the file
    while (charPlusOne = fin.peek())    // fin.peek() will preview the next character in the file 
    {
        if (isLetter(charPlusOne))
        {
            pos = fsmIdentifier[pos][0];
        }

        else if (isDigit(charPlusOne))
        {
            pos = fsmIdentifier[pos][0];
        }

        else
        {
            pos = fsmIdentifier[pos][1];
        }

        if (pos == 2)
        {
            arr[i] = '\0';
            break;
        }

        else if (pos == 3)
        {
            arr[i] = '\0';
            break;
        }

        else
        {
            arr[i++] = charPlusOne;
        }

        fin.get();  // fin.get() will get the next character in the file
    }
    return  arr;
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
    char character;

    // Make sure the file is open
    if (!fin.is_open())
    {
        cout << "Error opening file" << endl;
        exit(1);
    }

    // Loop through the file until the end of the file
    while (!fin.eof())
    {
        character = fin.get();  // fin.get() will get the next character in the file
        char ops[11] = { '+', '-', '*', '/', '=', '<', '>', '!', '&', '|', '%' };
        char seps[10] = { '(', ')', '{', '}', '[', ']', ',', ';', ':', '#' };

        // Check if the character is a letter
        if (isLetter(character))
        {
            int fsmIntReal[5][3] = {
                /*0*/               {1, 3, 3},
                /*1*/               {1, 2, 3},
                /*2*/               {2, 3, 3},
                /*3*/               {3, 3, 3},
                /*4*/               {4, 4, 4}
            };

            int i = 0;  // counter
            char IDarr[100];
            IDarr[i] = character;
            i++;
            char nextChar = fin.peek(); // fin.peek() will preview the next character in the file

            while (isNum(nextChar) || nextChar == '_')
            {
                IDarr[i] = nextChar;
                i++;
                fin.get();  // fin.get() will get the next character in the file
                nextChar = fin.peek();  // fin.peek() will preview the next character in the file
            }

            IDarr[++i] = '\0';

            string kWord = isKeyword(IDarr);
            
            if (kWord != "Not a keyword")
            {
                cout << kWord << " is a keyword" << endl;
                fout << kWord << " is a keyword" << endl;
            }
            else
            {
                cout << IDarr << " is an identifier" << endl;
                fout << IDarr << " is an identifier" << endl;
            }
        }

        // Check if the character is a digit
        else if (isDigit(character))
        {

        }

        //Check if it is an operator
        else if (checkArr(character, ops, 11))
        {

        }

        // Check if it is a separator
        else if (checkArr(character, seps, 10))
        {

        }
    }

    // Close the file
    fin.close();
    fout.close();
}

int main()
{

}