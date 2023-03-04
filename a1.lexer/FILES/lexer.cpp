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
#include <string.h>

using namespace std;

// Initialize the variables that will be used in the lexer
char currentChar;   // This will store the current character
char ch[100];        // This will store the characters from the source code file
int i = 0;          // This will be used to iterate through the array of stored characters

/* List our accepted operators and separators
char operators[] = { '+', '-', '*', '/', '=', '<', '>', '!', '&', '|', '%' };
char separators[] = { '(', ')', '{', '}', '[', ']', ',', ';', ':', '#' };

List our accepted keywords
string keywords[] = { "if", "then", "else", "end", "repeat", "until", "read", "write", "while", "do", "endwhile" };

*/
// NOTE: ID, INT, and REAL would be determined by the final state of the FSM

// List of the states that will be used in the FSM, will be false by default
bool endOfOp = false;
bool endOfSep = false;
bool endOfID = false;
bool endOfInt = false;
bool endOfReal = false;

bool isOp(char currentChar)
{
     string opString = "+-*/=<>!&|%";
     
     // Check if the current character is an operator
     if (opString.find(currentChar) != string::npos)
     {
          return true;
     }
     else
     {
          return false;
     }
}

bool isSep(char currentChar)
{
     string sepString = "(){}[],;:#";

     // Check if the current character is a separator
     if (sepString.find(currentChar) != string::npos)
     {
          return true;
     }
     else
     {
          return false;
     }
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

bool isKeyword(string input)
{
     vector<string> keywords = { "if", "then", "else", "end", "repeat", "until", "read", "write", "while", "do", "endwhile" };

     // Check if the input is a keyword
     if (find(keywords.begin(), keywords.end(), input) != keywords.end())
     {
          return true;
     }
     else
     {
          return false;
     }
}

int columnDeterminerFSM(char input)
{

}

// Here will be both FSMs

// FSM for Identifiers
int FSM_ID(int state, char input)
{

}

bool is_accepting_state_ID(int state)
{

}

// FSM for Integers and Reals
int FSM_IntReal(int state, char input)
{

}

bool is_accepting_state_IntReal(int state)
{

}

// Helper function that returns the token type based on the FSM state for Int and Real
string intRealState(int state)
{

}

// Helper function that returns the token type based on the FSM state for ID
string idState(int state)
{

}

// class for the tokens
class tokenLexeme
{
     private:
          string token;
          string lexeme;
     public:
          // constructor
          tokenLexeme()
          {
               token = "null";
               lexeme = "null";
          }

          // accessor functions
          string getToken()
          {
               return token;
          }

          string getLexeme()
          {
               return lexeme;
          }

          void updateToken(string newToken)
          {
               token = newToken;
          }

          void updateLexeme(string newLexeme)
          {
               lexeme = newLexeme;
          }

          // helper function to print 
          void initPrint()
          {
               cout << "Output:" << endl;
               cout << setw(10) << left << "Token" << setw(10) << left << "Lexeme" << endl;
               cout << setw(10) << left << "-----" << setw(10) << left << "------" << endl;
          }

          void print()
          {
               cout << setw(10) << left << token << setw(10) << left << lexeme << endl;
          }
};


// The lexer function
void lexer()
{

}


int main()
{
     // Open the users desired files
     string userFile, outputFile;
     cout << "Enter the name of the file you would like to open: " << endl;
     cin >> userFile;

     cout << "Enter the name of the file you would like to output to: " << endl;
     cin >> outputFile;

     // Open the files
     ifstream inFile;
     inFile.open(userFile);
     
     ofstream outFile;
     outFile.open(outputFile);

     // Logicical side of the main function
     if (!inFile.is_open())
     {
          cout << "Error opening file" << endl;
          exit(1);
     }

     // print out the table contents
     tokenLexeme token;
     token.initPrint();

     while (!inFile.eof())
     {
          // Read in the file
          inFile.get(currentChar);
          ch[i] = currentChar;
          i++;

          // Call the lexer function
          lexer();
     }

     // Close the files
     inFile.close();
     outFile.close();

     return 0;
}
