// Build of a lexer
// The lexer will be built entirely using a finite state machine

// MUST write the Regular Expressions for Identifiers, Real, and Integer
// Also show NFSM using Thompson's construction

/* Program must read a file containing the source code of the language to generate tokens and write out the 
   results to an output file. 
*/
// Print both, the tokens and lexemes

/* Psuedo code below:
     while not finished (i.e. not end of the source file) do
          call the lexer for a token
          print the token and lexeme
     endwhile
*/

/* Sample test case:

INPUT: while  (fahr <= upper)   a = 23.00; endwhile  [* this is sample *]

OUTPUT: 

token           lexeme
-----           ------
keyword         while
separator       (
identifier      fahr
operator        <=
identifier      upper
separator       )
identifier      a
operator        =
real            23.00
separator       ;
keyword         endwhile
*/

#pragma once

#include "lexer.hpp"

#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <cctype>

using namespace std;

// Find which FSM to use given the input
int FSM_determiner(char input)
{

}

// lexer
tokenLexeme lexer(string input)
{
     

}


int main()
{
     // chars that will store the characters from the source code file
     char currentChar;   // This will store the current character
     char ch[100];        // This will store the characters from the source code file

     // Open the source code file
     ifstream fin("input.txt");

     if(fin.is_open())
     {
          cout << "File opened successfully" << endl;
     }
     else
     {
          cout << "Unable to open file" << endl;
          exit(0);
     }

     // while not finished (i.e. not end of the source file) do
     //     call the lexer for a token
     //     receive the token and lexeme from vectors in lexer
     //     open the output file (output.txt)
     //     print the token and lexeme to the output file
     //     close the output file
     // end while

     while(!fin.eof())
     {
          currentChar = fin.get(); // Get the current character from the source code file
          for (int i = 0; i < 100; i++)
          {
               ch[i] = currentChar; // Store the current character into the array
          }
     }

     // Close the source code file and call lexer
     fin.close();
     lexer(ch);

     return 0;
}
