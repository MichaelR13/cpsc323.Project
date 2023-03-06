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

/* List our accepted operators and separators
char operators[] = { '+', '-', '*', '/', '=', '<', '>', '!', '&', '|', '%' };
char separators[] = { '(', ')', '{', '}', '[', ']', ',', ';', ':', '#' };

List our accepted keywords
string keywords[] = { "if", "then", "else", "end", "repeat", "until", "read", "write", "while", "do", "endwhile" };

*/
// NOTE: ID, INT, and REAL would be determined by the final state of the FSM

// List of the states that will be used in the FSM, will be false by default
/*
bool endOfOp = false;
bool endOfSep = false;
bool endOfID = false;
bool endOfInt = false;
bool endOfReal = false;
*/

bool isOp(char input)
{
     vector<char> operators = { '+', '-', '*', '/', '=', '<', '>', '!', '&', '|', '%' };
     
     // Check if the current character is an operator
     if (find(operators.begin(), operators.end(), input) != operators.end())
     {
          return true;
     }
     else
     {
          return false;
     }
}

bool isSep(char input)
{
     vector<char> separators = { '(', ')', '{', '}', '[', ']', ',', ';', ':', '#' };
     
     // Check if the current character is a separator
     if (find(separators.begin(), separators.end(), input) != separators.end())
     {
          return true;
     }
     else
     {
          return false;
     }

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

bool isLetter(char input)
{
     string letterString = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";

     // Check if the input is a letter
     if (letterString.find(input) != string::npos)
     {
          return true;
     }
     else
     {
          return false;
     }
}

bool isDigit(char input)
{
     string digitString = "0123456789";

     // Check if the input is a digit
     if (digitString.find(input) != string::npos)
     {
          return true;
     }
     else
     {
          return false;
     }
}

bool isUnderscore(char input)
{
     char underscore = '_';
     if (input == underscore)
     {
          return true;
     }
     else
     {
          return false;
     }
}

bool isPeriod(char input)
{
     char period = '.';
     if (input == period)
     {
          return true;
     }
     else
     {
          return false;
     }
}

bool isWS(char input)
{
     string whiteSpace = "\n\t ";
     
     if (whiteSpace.find(input) != string::npos)
     {
          return true;
     }

     else
     {
          return false;
     }
}

// Helper function that determines other operators and separators
string opSep(char input)
{
    // Use isOp and isSep to determine if the input is an operator or separator
    switch (input)
    {
     case '+':
           return "operator";
           break;
     case '-':
               return "operator";
               break;
     case '*':
               return "operator";
               break;
     case '/':
               return "operator";
               break;
     case '=':
               return "operator";
               break;
     case '<':
               return "operator";
               break;
     case '>':
               return "operator";
               break;
     case '!':
               return "operator";
               break;
     case '&':
               return "operator";
               break;
     case '|':
               return "operator";
               break;
     case '%':
               return "operator";
               break;
     case '(':
               return "separator";
               break;
     case ')':
               return "separator";
               break;
     case '{':
               return "separator";
               break;
     case '}':
               return "separator";
               break;
     case '[':
               return "separator";
               break;
     case ']':
               return "separator";
               break;
     case ',':
               return "separator";
               break;
     case ';':
               return "separator";
               break;
     case ':':
               return "separator";
               break;
     case '#':
               return "separator";
               break;
     default:
               return "OpSep error";
               break;
     }
}

int columnDeterminerFSM(char input)
{
     int column;

     if (isLetter(input))
     {
          column = 0;
     }

     else if (isDigit(input))
     {
          column = 1;
     }

     else if (isUnderscore(input))
     {
          column = 2;
     }

     else if (isPeriod(input))
     {
          column = 3;
     }

     else
     {
          column = 4;
     }

     return column;
}

// Here will be both FSMs

// FSM for Identifiers
int isID(int state, char input)
{

     int stateID[5][5] = 
     {
     {2, 2, 2, 3, 4},
     {2, 2, 2, 3, 4},
     {4, 4, 4, 4, 5},
     {5, 5, 5, 5, 5},
     {5, 5, 5, 5, 5}
     };

     int stateRow = state - 1;
     int stateColumn = columnDeterminerFSM(input);
     return stateID[stateRow][stateColumn]; 
}

bool is_accepting_state_ID(int state)
{
     if (state == 1 || state == 2 || state == 3)  // 1, 2, and 3 are the accepting states for ID
     {
          return true;
     }
     else
     {
          return false;
     }
}

// FSM for Integers and Reals
int isIntReal(int state, char input)
{
     int stateIntReal[7][5] = {
     {4, 2, 4, 3, 5},
     {4, 2, 4, 3, 5},
     {4, 3, 4, 4, 6},
     {4, 4, 4, 4, 7},
     {7, 7, 7, 7, 7},
     {7, 7, 7, 7, 7},
     {7, 7, 7, 7, 7}
     };

     int stateRow = state - 1;
     int stateColumn = columnDeterminerFSM(input);
     return stateIntReal[stateRow][stateColumn];
}

bool is_accepting_state_IntReal(int state)
{
    if (state == 1 || state == 2 || state == 3 || state == 4) // 1, 2, 3, and 4 are the accepting states for Int and Real
     {
          return true;
     }
     else
     {
          return false;
     }
}

// Helper function that returns the token type based on the FSM state for Int and Real
string intRealState(int state)
{
     if (state == 5) 
     {
          return "Integer";
     }
     else if (state == 6) 
     {
          return "Real";
     }
     else if (state == 7)
     {
          return "Invalid token";
     }
     else
     {
          return "error in intRealState";     // NOTE: this output is being looped infinitely
     }
}

// Helper function that returns the token type based on the FSM state for ID
string idState(int state)
{
     if (state == 4) 
     {
          return "Identifier";
     }
     else if (state == 5) 
     {
          return "Invalid Token";
     }
     else
     {
          return "error in idState";
     }
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
tokenLexeme lexer(ifstream &inFile)
{
     tokenLexeme giveTok;
     char inChar;
     int state = 1;

     // Read the first character of the file
     inFile.get(inChar);
     string tokString = "";   // has to be empty for the first character
     tokString.push_back(inChar);  // push the first character into the string

     // Now check which FSM to use
     if (isDigit(inChar))     // int or real
     // Ex: 23.45 is a real
     // Ex: 23 is an integer
     {
          while (inFile.eof() != true && is_accepting_state_IntReal(state))    // This will read chars until a token is made
          {
               inFile.get(inChar);
               tokString.push_back(inChar);
               state = isIntReal(state, inChar);
          }
          if (inFile.eof() != true) // This will unget the last char if it is not the end of the file
          {
               inFile.unget();
               tokString.pop_back();
          }

          string returnToken = intRealState(state);
          string returnLexeme = tokString;

          giveTok.updateLexeme(returnLexeme);
          giveTok.updateToken(returnToken);

          return giveTok;
     }

     else if (isLetter(inChar))    // Identifier
     {
          while (inFile.eof() != true && is_accepting_state_ID(state))    // This will read chars until a token is made
          {
               inFile.get(inChar);
               tokString.push_back(inChar);
               state = isID(state, inChar);
          }
          if (inFile.eof() != true) // This will unget the last char if it is not the end of the file
          {
               inFile.unget();
               tokString.pop_back();
          }

          string returnToken = idState(state);
          string returnLexeme = tokString;

          giveTok.updateLexeme(returnLexeme);

          if (isKeyword(returnLexeme))
          {
               returnToken = "KEYWORD";
          }

          giveTok.updateToken(returnToken);

          return giveTok;
     }

     else if (isWS(inChar))
     {
          string returnToken = "Whitespace";
          string returnLexeme = tokString;

          giveTok.updateToken(returnToken);
          giveTok.updateLexeme(returnLexeme);

          return giveTok;
     }

     else if (inChar = '\0' || inFile.eof()) // This will check if the file is empty
     {
          cout << "error" << endl;

          return giveTok;
     }

     else // other ops and seps 
     {
          string returnToken = opSep(inChar);
          string returnLexeme = tokString;

          char holder;

          if (returnLexeme == "$")
          {
               inFile.get(holder);

               if (holder == '$')
               {
                    returnLexeme += holder;
               }

               else
               {
                    inFile.unget();
               }
          }

          else if (returnLexeme == "!")
          {
               inFile.get(holder);

               if (holder == '=')
               {
                    returnLexeme += holder;
               }

               else
               {
                    inFile.unget();
               }
          }

          else if (returnLexeme == "=")
          {
               inFile.get(holder);
               
               if (holder == '=' || holder == '>')
               {
                    returnLexeme += holder;
               }
               
               else
               {
                    inFile.unget();
               }
        }

          else if (returnLexeme == "<")
          {
               inFile.get(holder);
               if (holder == '=')
               {
                    returnLexeme += holder;
               }
               else
               {
                    inFile.unget();
               }
          }

          else if (returnLexeme == "/")
          {
               inFile.get(holder);

               if (holder == '*')
               {
                    bool loop = true;

                    while (loop == true)
                    {
                         inFile.get(holder);

                         if (holder == '*')
                         {
                              inFile.get(holder);

                              if (holder == '/')
                              {
                                   loop = false;
                                   returnLexeme == "null";
                                   returnToken == "null";
                              }

                              else
                              {
                                   inFile.unget();
                              }
                         }
                    }
               }

               else
               {
                    inFile.unget();
               }

          }

          giveTok.updateToken(returnToken);
          giveTok.updateLexeme(returnLexeme);

          return giveTok;

     }
}


int main()
{
     // Ask user for the input file
     string inFileName;
     // string outFileName = "output.txt";
     cout << "Enter the input file name: ";
     cin >> inFileName;
     ifstream inFile(inFileName);
     // ofstream outFile(outFileName);

     // Check if the input file is open
     if (!inFile.is_open())
     {
          cout << "Error opening file" << endl;
          return 0;
     }

     /*
     // Check if the output file is open
     if (!outFile.is_open())
     {
          cout << "Error opening file" << endl;
          return 0;
     }
     */
     /*
     // Create a tokenLexeme object
     tokenLexeme token;

     // Print the header
     token.initPrint();

     // Call the lexer function
     token = lexer(inFile);

     // Print the token and lexeme
     token.print();
     */

     // Because the code above is only outputting one token and lexeme, I will:
     // Clone the contents of the input file into "helper.txt"
     // Call initPrint() once
     // 1. Use the lexer and print the 1st token/lexeme pair
     // 2. Output that pair into the terminal
     // 3. Delete the lexeme from the cloned input file
     // Repeat steps 1-3 until the cloned file is empty
     fstream hFile;

     string nameH = "helper.txt";
     
     hFile.open(nameH, ios::out);

     string contents;

     while (!inFile.eof())
     {
          getline(inFile, contents);

          hFile << contents << endl;
     }
     inFile.close();
     hFile.close(); // helper.txt now has all we need

     // Open clone file for reading
     ifstream hFile(nameH);

     if (!hFile.is_open())
     {
          cout << "Error opening cloned file" << endl;
          return 0;
     }

     tokenLexeme token;

     token.initPrint();

     // Now comence steps 1-3, until the helper.txt is empty
     

     return 0;
}