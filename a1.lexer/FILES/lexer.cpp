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

#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <cctype>

using namespace std;

// Initialize the variables that will be used in the lexer
char currentChar;   // This will store the current character
char ch[100];        // This will store the characters from the source code file
int i = 0;          // This will be used to iterate through the array of stored characters

// List our accepted operators and separators
char operators[] = { '+', '-', '*', '/', '=', '<', '>', '!', '&', '|', '%' };
char separators[] = { '(', ')', '{', '}', '[', ']', ',', ';', ':', '#' };

// List our accepted keywords
string keywords[] = { "if", "then", "else", "end", "repeat", "until", "read", "write", "while", "do", "endwhile" };

// NOTE: ID, INT, and REAL would be determined by the final state of the FSM

// List of the states that will be used in the FSM, will be false by default
bool endOfOp = false;
bool endOfSep = false;
bool endOfID = false;
bool endOfInt = false;
bool endOfReal = false;

bool isOp(char currentChar)
{

}

bool isSep(char currentChar)
{

}

bool isID(char currentChar)
{

}

bool isInt(char ch[])
{

}

bool isReal(char ch[])
{

}

// Find which FSM to use given the input
int FSM_determiner(char input)
{

}

// lexer
tokenLexeme lexer(string input)
{
     tokenLexeme returnTok;
     int state = 1; // This will hold the current state of the FSM
     char inputChar; // This will hold the current character of the input
     string tokString = ""; // This will hold the lexeme
     tokString.push_back(inputChar); // Add the current character to the lexeme

     // Now check the first char and determine which FSM to use
     // Case for Integer and Reals
     if (isdigit(inputChar))
     {
          // Read char until it terminate with a token
     }

     // Case for Identifiers
     else if (isalpha(inputChar))
     {
          // Read char until it terminate with a token
     }

     // Case for other sep/ops
     else
     {
          // Read char until it terminate with a token
     }
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
