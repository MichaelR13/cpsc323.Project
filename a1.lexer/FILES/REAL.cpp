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

// function prototypes
void openFiles();
void initPrint();
void endPrint();
bool checkArr(char value, char* array, int size);
string intRealFSM(char num);
string isKeyword(char buf[]);
void lexer();

// global variables
ifstream fin;   // input file
ofstream fout;  // output file

// function that asks the user for a file name 

void openFiles()
{
    string inFile;
    cout << "Enter the name of the file you want to open: ";
    cin >> inFile;
    
    string outFile = "output.txt";
    
    // Now open the files
    fin.open(inFile);
    fout.open(outFile);

    // Check if the files are open
    if (!fin.is_open() || !fout.is_open())
    {
        cout << "Error opening file" << endl;
        exit(0);
    }
}

void initPrint()// This will print the header for the output file
{
    cout << "lexeme___________________token" << endl;
    fout << "lexeme___________________token" << endl;
}

// Check if a value in the array matches
bool checkArr(char value, char* array, int size)
{
    for (int counter = 0; counter < size; counter++)
    {
        if (value == array[counter])
        {
            return true;
        }
    }
}

void endPrint() // This will print the footer for the output file
{
    cout << "\n\nEND OF FILE\n\n" << endl;
    fout << "\n\nEND OF FILE\n\n" << endl;
}

// FSM for integers and real numbers
string intRealFSM(char num) {

    // There will be 3 states: 1 - Integer, 2 - Real, 3 - Error
    int fsmIntReal[5][3] = {
        /*0*/               {1, 3, 3},
        /*1*/               {1, 2, 3},
        /*2*/               {2, 3, 3},
        /*3*/               {3, 3, 3}
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
        if (isdigit(charPlusOne))
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

        else
        {
            arr[i++] = charPlusOne;
        }

        fin.get();  // fin.get() will get the next character in the file
    }
    return arr;
}

string isKeyword(char buf[])    // this function will check if the identifier is a keyword
{
    string keywords[11] = { "if", "then", "else", "end", "repeat", "until", "read", "write", "while", "do", "endwhile" };
    int counter = 0;  // counter
    
    for (counter = 0; counter < 11; ++counter)
    {
        if (strcmp(keywords[counter].c_str(), buf) == 0)
        {
            return keywords[counter];
        }
    }
    return "-1";
}

void lexer()
{
    char character; // This will hold the character that is being read from the file

    // Loop through the file until the end of the file
    while (!fin.eof())
    {
        character = fin.get();  // fin.get() will get the next character in the file
        char ops[10] = { '+', '-', '*', '/', '=', '<', '!', '&', '|', '%' };
        char seps[12] = { '%', '(', ')', '{', '}', '[', ']', ',', ';', ':', '#', '*' };

        // Check if the character is a letter
        if (isalpha(character))
        {
            int fsmIntReal[4][3] = {
                /*0*/               {1, 3, 3},
                /*1*/               {1, 2, 3},
                /*2*/               {2, 3, 3},
                /*3*/               {3, 3, 3},
            };

            int i = 0;  // counter
            char IDarr[100];
            IDarr[i] = character;
            char nextChar = fin.peek(); // fin.peek() will preview the next character in the file

            while (isalnum(nextChar) || nextChar == '_')
            {
                i++;
                IDarr[i] = nextChar;
                fin.get();  // fin.get() will get the next character in the file
                nextChar = fin.peek();  // fin.peek() will preview the next character in the file
            }

            IDarr[++i] = '\0';

            string kWord = isKeyword(IDarr);
            
            if (kWord != "-1")
            {
				cout << kWord << "\t\t\tkeyword\n";
				fout << kWord << "\t\t\tkeyword\n";
            }
            else
            {
				cout << IDarr << "\t\t\tidentifier\n";
				fout << IDarr << "\t\t\tidentifier\n";
            }
        }

        // Check if the character is a digit
        else if (isdigit(character))
        {
            string num = intRealFSM(character); // This will hold the number that is being read from the file

			if (num.find(".") != -1) 
            {
				cout << num << "\t\t\treal\n";
				fout << num << "\t\t\treal\n";
            }
            else
            {
				cout << num << "\t\t\tinteger\n";
				fout << num << "\t\t\tinteger\n";
            }
        }

        //Check if it is an operator
        else if (checkArr(character, seps, 10))
        {
            char nextChar = fin.peek(); // fin.peek() will preview the next character in the file
			
            if (nextChar == '%')
            {
				cout << character << nextChar << "\t\t\tseperator\n";
				fout << character << nextChar << "\t\t\tseperator\n";
				fin.get();
			}
			else if (nextChar == ']')
            { 
				cout << character << nextChar << "\t\t\tseperator\n";
				fout << character << nextChar << "\t\t\tseperator\n";
				fin.get();
			}
			else if (nextChar == '*')
            { 
				cout << character << nextChar << "\t\t\tseperator\n";
				fout << character << nextChar << "\t\t\tseperator\n";
				fin.get();
				char seeker;
				while(seeker != '*'){
					fin.get(seeker);
				}
				fin.unget();
			}
			else if (character == '*')
            {
				cout << character << "\t\t\toperator\n";
				fout << character << "\t\t\toperator\n";
			}
            // Remove any whitespace
            else if (character == ' ')
            {
                continue;
            }
            // multiple character operators (<=, >=, ==, !=, &&, ||)
            else if (character == '<' || character == '>' || character == '=' || character == '!' || character == '&' || character == '|')
            {
                if (nextChar == '=')
                {
                    cout << character << nextChar << "\t\t\toperator\n";
                    fout << character << nextChar << "\t\t\toperator\n";
                    fin.get();  // fin.get() will get the next character in the file
                }
                else
                {
                    cout << character << "\t\t\toperator\n";
                    fout << character << "\t\t\toperator\n";
                }
            }

            else
            {
				cout << character << "\t\t\tseperator\n";
				fout << character << "\t\t\tseperator\n";
            }
        }

        // Check if it is a separator
        else if (checkArr(character, ops, 12))
        {
            char nextChar = fin.peek(); // fin.peek() will preview the next character in the file

            if (nextChar == '>')
            {
				cout << character << nextChar << "\t\t\toperator\n";
				fout << character << nextChar << "\t\t\toperator\n";
                fin.get();  // fin.get() will get the next character in the file
            }
            else if (nextChar == '=')
            {
				cout << character << nextChar << "\t\t\toperator\n";
				fout << character << nextChar << "\t\t\toperator\n";
                fin.get();  // fin.get() will get the next character in the file
            }
            else
            {
				cout << character << "\t\t\toperator\n";
				fout << character << "\t\t\toperator\n";
            }

        }
    }

    // Close the file
    fin.close();
    fout.close();
}

int main()
{
    openFiles();    // Ask the user for the file name and open the file
    initPrint();    // Print the header
    lexer();    // Run the lexer
    endPrint(); // Print the footer
    return 0;
}