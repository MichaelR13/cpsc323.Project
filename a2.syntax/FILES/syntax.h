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

/*
Syntax rules : The following BNF describes the Rat23S. 
R1. <Rat23S> ::= <Opt Function Definitions> # <Opt Declaration List> # <Statement List> 
R2. <Opt Function Definitions> ::= <Function Definitions> | <Empty>
R3. <Function Definitions> ::= <Function> | <Function> <Function Definitions> 
R4. <Function> ::= function <Identifier> ( <Opt Parameter List> ) <Opt Declaration List> <Body>
R5. <Opt Parameter List> ::= <Parameter List> | <Empty>
R6. <Parameter List> ::= <Parameter> | <Parameter> , <Parameter List>
R7. <Parameter> ::= <IDs > <Qualifier> 
R8. <Qualifier> ::= int | bool | real 
R9. <Body> ::= { < Statement List> }
R10. <Opt Declaration List> ::= <Declaration List> | <Empty>
R11. <Declaration List> := <Declaration> ; | <Declaration> ; <Declaration List>
R12. <Declaration> ::= <Qualifier > <IDs> 
R13. <IDs> ::= <Identifier> | <Identifier>, <IDs>
R14. <Statement List> ::= <Statement> | <Statement> <Statement List>
R15. <Statement> ::= <Compound> | <Assign> | <If> | <Return> | <Print> | <Scan> | <While> 
R16. <Compound> ::= { <Statement List> } 
R17. <Assign> ::= <Identifier> = <Expression> ;
R18. <If> ::= if ( <Condition> ) <Statement> fi | 
 if ( <Condition> ) <Statement> else <Statement> fi
R19. <Return> ::= return ; | return <Expression> ;
R21. <Print> ::= put ( <Expression>);
1
R21. <Scan> ::= get ( <IDs> );
R22. <While> ::= while ( <Condition> ) <Statement> endwhile
R23. <Condition> ::= <Expression> <Relop> <Expression>
R24. <Relop> ::= == | != | > | < | <= | => 
R25. <Expression> ::= <Expression> + <Term> | <Expression> - <Term> | <Term>
R26. <Term> ::= <Term> * <Factor> | <Term> / <Factor> | <Factor>
R27. <Factor> ::= - <Primary> | <Primary>
R28. <Primary> ::= <Identifier> | <Integer> | <Identifier> ( <IDs> ) | ( <Expression> ) | 
 <Real> | true | false 
R29. <Empty> ::= 
Note: <Identifier>, <Integer>, <Real> are token types as defined in section (1) above
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
#include <vector>

using namespace std;

// function prototypes
void readToken();       // Read the token and lexeme from the lexer output file
void leftRecursion();   // Remove left recursion from the grammar (use left factorization if needed)
void errorHandler();    // Generate error messages for syntax errors
void parser();          // Use a Recursive Descent Parser (RDP) to parse the input
void syntax();
void openSyntaxFile();
void closeSyntaxFile();

// Debug prototypes
void tester();

// Global variables
ifstream lexerOutput;   // input file
ofstream syntaxOutput;  // output file
vector<string> token;
vector<string> lexeme;

// function that opens the output file from the lexer and converts into a 2 vectors (token and lexeme)
// NOTE: This function will read the output file from the lexer, and add the to token and lexeme vectors
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

*/
void readToken()
{
    // open the output file from the lexer
    lexerOutput.open("lexerOutput.txt");

    // check if the file is open
    if (!lexerOutput.is_open())
    {
        cout << "Error: Could not open the output file from the lexer" << endl;
        exit(0);
    }

    // read the output file from the lexer, and add the to token and lexeme vectors
    // NOTE: Use 2 consecutive, empty characters to distinguish between the start and end of tokens/lexemes
    /*
    lexeme vector:
    while, (, fahr, <=, upper, ), a, =, 23.00, ;, endwhile

    token vector:
    keyword, seperator, identifier, operator, identifier, seperator, identifier, operator, real, seperator, keyword        
    */
    string temp;
    while (lexerOutput >> temp)
    {
        // add the token to the token vector
        token.push_back(temp);

        // add the lexeme to the lexeme vector
        lexerOutput >> temp;
        lexeme.push_back(temp);
    }

    // close the output file from the lexer
    lexerOutput.close();

    // add 2 empty strings to the end of the vectors, to distinguish between the start and end of tokens/lexemes
    token.push_back("");
    lexeme.push_back("");

    // Debug: print out the token and lexeme vectors
    tester();
}

// function that handles the errors
void errorHandling()
{
    
}

// function that opens the output file that will store the output of the syntax analyzer
void openSyntaxFile()
{
    string syntaxOutputFile;
    cout << "Enter the name of the file you want to output to";
    cout << " (include the file extension): ";
    cin >> syntaxOutputFile; // cin >> outFile;

    syntaxOutput.open(syntaxOutputFile);

    if (!syntaxOutput.is_open())
    {
        cout << "Error opening syntax output file" << endl;
        exit(0);
    }
}

// function that closes the output file that will store the output of the syntax analyzer
void closeSyntaxFile()
{
    syntaxOutput.close();

    if (syntaxOutput.is_open())
    {
        cout << "Error closing file" << endl;
        exit(0);
    }
}

// Debug function that tests if the correct strings were added to the vectors, by printing them out
void tester()
{
    // print out the token vector and write to the output file
    cout << "\nToken vector: " << endl;
    syntaxOutput << "\nToken vector: " << endl;
    for (int i = 0; i < token.size(); i++)
    {
        cout << token[i] << endl;
        syntaxOutput << token[i] << endl;
    }

    // print out the lexeme vector
    cout << "\nLexeme vector: " << endl;
    syntaxOutput << "\nLexeme vector: " << endl;
    for (int i = 0; i < lexeme.size(); i++)
    {
        cout << lexeme[i] << endl;
        syntaxOutput << lexeme[i] << endl;
    }
}

// main function for syntax analyzer
void syntax()
{
    
}

#endif