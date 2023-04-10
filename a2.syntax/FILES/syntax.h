// Assignment 2

/*
The second assignment is to write a syntax analyzer. You may use any top-down parser such as RDP, 
a predictive recursive descent parser or a table-driven predictive parser.
Hence, your assignment consists of the following tasks:
1. Rewrite the grammar Rat23S to remove any left recursion
 (Also, use left factorization if necessary) 
2. Use the lexer() generated in the assignment 1 to get the tokens
3. The parser should print to an output file the tokens, lexemes and 
 the production rules used;
 That is, first, write the token and lexeme found
 Then, print out all productions rules used for analyzing this token
 Note: - a simple way to do it is to have a “print statement” at the beginning of each function that will print 
 the production rule.
 - It would be a good idea to have a “switch” with the “print statement” so that you can turn it on or off.
4. Error handling: if a syntax error occurs, your parser should generate a meaningful error message, such as 
token, lexeme, line number, and error type etc. 
Then, your program may exit or you may continue for further analysis.
The bottom line is that your program must be able to parse the entire program if it is syntactically correct.
*/

/* Example:

code: a = b + c;

possible output:

    Token: Identifier Lexeme: a
        <Statement> -> <Assign>
        <Assign> -> <Identifier> = <Expression> ;

    Token: Operator Lexeme: =

    Token: Identifier Lexeme: b
        <Expression> -> <Term> <Expression Prime>
        <Term> -> <Factor> <Term Prime>
        <Factor> -> <Identifier>

    Token: Operator Lexeme: +
        <Term Prime> -> epsilon
        <Expression Prime> -> + <Term> <Expression Prime>

    Token: Identifier Lexeme: c
        <Term> -> <Factor> <Term Prime>
        <Factor> -> <Identifier>
    
    Token: Separator Lexeme: ;
        <Term Prime> -> epsilon
        <Expression Prime> -> epsilon
    
    ..more...
*/

/* One Possible Example:

Productions:
E -> TE’
E’ -> + TE’ | - TE’ | ε
T -> id

Procedure E ()
{
    if switch print (“ E -> TE’); // switch is a boolean
    T ();
    E’();
    If not eof marker then
        error-message 
}

Procedure E’()
{
    if switch print (“ E’ -> +TE’ | - TE’ | ε”);
    If token = + or – then
    {
        lexer();
        T();
        E’();
    }
}

Procedure T();
{
    if switch print (“ T -> id”);
    If token is id then 
        lexer();
    else
        error-message (id expected)
}

*/

// NOTE: Only exit when there is a syntax error
// 36 functions, Output is printf statements (in a debug way)

#ifndef SYNTAX_H
#define SYNTAX_H

#include "lexer.h"

#include <iostream>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string>
#include <string.h>

using namespace std;

// function prototypes
void readToken();
void errorHandling();
void syntax();
void openSyntaxFile();
void closeSyntaxFile();

// Global variables

// function that opens the output file from the lexer and reads the tokens
// NOTE: This function will read the output file from the lexer, and add the to token and lexeme arrays
/* Ex:
output file from lexer:
while			keyword
(			seperator
fahr			identifier
<=			operator
upper			identifier
)			seperator
a			identifier
=			operator
23.00			real
;			seperator
endwhile			keyword

lexeme array:
while, (, fahr, <=, upper, ), a, =, 23.00, ;, endwhile

token array:
keyword, seperator, identifier, operator, identifier, seperator, identifier, operator, real, seperator, keyword

*/
void readToken()
{
            
}

// function that handles the errors
void errorHandling()
{
    
}

// function that opens the output file that will store the output of the syntax analyzer
void openSyntaxFile()
{
    
}

// function that closes the output file that will store the output of the syntax analyzer
void closeSyntaxFile()
{
    
}

// main function for syntax analyzer
void syntax()
{
    
}

#endif