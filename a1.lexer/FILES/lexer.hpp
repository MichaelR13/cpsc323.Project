// This will be the lexer class, which will be used to tokenize the input
// 6 token types: keywords, identifiers, operators, separators, integers, and reals
// It will primarily token definitions, as well as the lexer class

#pragma once

#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <cctype>

using namespace std;

//functions that will be used to find the input type
bool isOperator(char input);
bool isSeparator(char input);
bool isKeyword(string input);
bool isWhitespace(char input);
string isOpOrSep(char input);

// Make 2 finite state machines, one for the Identifier and one for Integer + Real
// Helper function that determines the column of the FSM
int columnDeterminerFSM(char input);

// Finite State Machine for Identifiers
int FSM_ID(int state, char input); // This function will return the next state of the FSM
bool is_accepting_state_ID(int state); // This function will determine if the FSM is in an accepting state

// Finite State Machine for Integers and Reals
int FSM_IntReal(int state, char input); // This function will return the next state of the FSM
bool is_accepting_state_IntReal(int state); // This function will determine if the FSM is in an accepting state

// Find out the token type using the final state of the FSM
string endOfIntReal(int state); 
string endOfID(int state);

// Add an instruction table to the lexer that w


// Start lexer function

class tokenLexeme // This class will hold the token and lexeme
{
    private:
        string token;   // This will hold the token
        string lexeme;  // This will hold the lexeme

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

        // mutator functions
        void setToken(string getToken)
        {
            token = getToken;
        }
        
        void setLexeme(string getLexeme)
        {
            lexeme = getLexeme;
        }
};

tokenLexeme lexer(string input_file); // This function will return the token and lexeme to the main function

