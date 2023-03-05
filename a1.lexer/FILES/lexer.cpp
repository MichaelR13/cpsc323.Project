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

// Helper function that determines other separators
string opSep(char input)
{
     if (isOp(input) != 0)
     {
          return "operator";
     }
     else if (isSep(input) != 0)
     {
          return "separator";
     }
     else
     {
          return "other separator";
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

     int stateID[5][5] = {
          // L,  D,  _,  .,  E
          {1, 2, 3, 4, 5},    
          {1, 1, 1, 1, 1},
          {2, 2, 2, 2, 2},
          {3, 3, 3, 3, 3},
          {4, 4, 4, 4, 4}
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
     int stateIntReal[5][5] = {
          // L,  D,  _,  .,  E
          {1, 2, 3, 4, 5},    
          {1, 1, 1, 1, 1},
          {2, 2, 2, 2, 2},
          {3, 3, 3, 3, 3},
          {4, 4, 4, 4, 4}
     };

     int stateRow = state - 1;
     int stateColumn = columnDeterminerFSM(input);
     return stateIntReal[stateRow][stateColumn];
}

bool is_accepting_state_IntReal(int state)
{
     if (state == 1 || state == 2)  // 1 and 2 are the accepting states for Int and Real
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
     if (state == 1)
     {
          return "INT";
     }
     else if (state == 2)
     {
          return "REAL";
     }
     else
     {
          return "null";
     }
}

// Helper function that returns the token type based on the FSM state for ID
string idState(int state)
{
     if (state == 1)
     {
          return "ID";
     }
     else
     {
          return "null";
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
tokenLexeme lexer(ifstream &inFile, ofstream &outFile)
{
     tokenLexeme token;
     char inChar;
     int state = 1;

     // Read the first character of the file
     inFile.get(inChar);
     string tokString = "";   // has to be empty for the first character
     tokString.push_back(inChar);  // push the first character into the string

     // Now check which FSM to use
     if (isDigit(inChar))     // int or real
     {
          while (!inFile.eof() != true && is_accepting_state_IntReal(state))    // This will read chars until a token is made
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

          token.updateToken(returnToken);
          token.updateLexeme(returnLexeme);

          return token;
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

          token.updateLexeme(returnLexeme);

          if (isKeyword(returnLexeme))
          {
               returnToken = "KEYWORD";
          }

          token.updateToken(returnToken);

          return token;
     }

     else if (inChar = '\0' || inFile.eof()) // This will check if the file is empty
     {
          cout << "error" << endl;

          return token;
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

          token.updateToken(returnToken);
          token.updateLexeme(returnLexeme);

          return token;

     }
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
