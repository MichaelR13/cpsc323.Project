// Grammar for rat23s language
/*
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
*/

// Now Rewrite the grammar Rat23S to remove any left recursion (use left factoring if necessary)
/*
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
R21. <Scan> ::= get ( <IDs> );
R22. <While> ::= while ( <Condition> ) <Statement> endwhile
R23. <Condition> ::= <Expression> <Relop> <Expression>
R24. <Relop> ::= == | != | > | < | <= | =>
R25. <Expression> ::= <Term> <Expression Prime>
R26. <Expression Prime> ::= + <Term> <Expression Prime> | - <Term> <Expression Prime> | <Empty>
R27. <Term> ::= <Factor> <Term Prime>
R28. <Term Prime> ::= * <Factor> <Term Prime> | / <Factor> <Term Prime> | <Empty>
R29. <Factor> ::= - <Primary> | <Primary>
R30. <Primary> ::= <Identifier> <Primary Prime> | <Integer> | <Identifier> ( <IDs> ) | ( <Expression> ) |
 <Real> | true | false
R31. <Primary Prime> ::= ( <IDs> ) | <Empty>
R32. <Empty> ::=
*/

// Now make a Recursive Descent Parser for the Rat23S language and print to an output file the tokens, lexemes, and production rules used
// NOTE: generate a meaningful error message if a syntax error is found
// Sample output for statement: a = b + c; is:
/*
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
#ifndef TEST_H
#define TEST_H

#include <iostream>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string>
#include <cstring>
#include <vector>
#include <iomanip>

#include "lexer.h"
#include "syntax.h"

using namespace std;

// Global variables
ifstream lexerOutput;   // input file
ofstream syntaxOutput;  // output file
vector<string> token;
vector<string> lexeme;

int tokCounter = -1;    // counter for the token vector
int lexCounter = -1;    // counter for the lexeme vector

// Function definitions

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

// function that reads the output file from the lexer, and add the to token and lexeme vectors
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
    //tester();
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

// Helper functions
void setTokCounter(int num)
{
    tokCounter = num;
}

int getTokCounter()
{
    return tokCounter;
}

void setLexCounter(int num2)
{
    lexCounter = num2;
}

int getLexCounter()
{
    return lexCounter;
}

vector <string> getTok()
{
    return token;
}

vector <string> getLex()
{
    return lexeme;
}

vector <string> getNextTok()
{
    tokCounter++;
    return getTok();
}

vector <string> getNextLex()
{
    lexCounter++;
    return getLex();
}


// START OF RECURSIVE DESCENT PARSER
bool Aprime()
{
    if (A())
    {
        return true;
    }
    else
    {
        return false;
    }
}

//
bool A()
{
    if (B())
    {
        if (getNextTok()[0] == "Separator" && getTok()[1] == "%%")
        {
            if (J())
            {
                if (N())
                {
                    if (getNextTok()[0] == "Separator" && getTok()[1] == "%%")
                    {
			            fout << "<Rat19F>  ::=   <Opt Function Definitions>   %%  <Opt Declaration List>  <Statement List>  %%" << endl;
                        cout << "<Rat19F>  ::=   <Opt Function Definitions>   %%  <Opt Declaration List>  <Statement List>  %%" << endl;
                        return true;
                    }
                }
            }
        }
    }
    else
    {
        return false;
    }
}

//
bool B()
{
    int tempTokCounter = getTokCounter();

    if (C())
    {
        fout << "<Opt Function Definitions> ::= <Function Definitions> " << endl;
        cout << "<Opt Function Definitions> ::= <Function Definitions> " << endl;
        return true;
    }

    else
    {
        setTokCounter(tempTokCounter);
        fout << "<Opt Function Definitions> ::= <Empty> " << endl;
        cout << "<Opt Function Definitions> ::= <Empty> " << endl;
        return true;
    }
}

//
bool C()
{
    
}

#endif