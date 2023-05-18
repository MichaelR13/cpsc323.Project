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

#ifndef GRAMMAR_H
#define GRAMMAR_H

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

// Function prototypes
void openSyntaxFile();
void closeSyntaxFile();
void readToken();
void tester();
void syntax();

// Recursive descent parser function prototypes
bool rat23S();
bool optFunctionDefinitions();
bool functionDefinitions();
bool function();
bool optParameterList();
bool parameterList();
bool parameter();
bool qualifier();
bool body();
bool optDeclarationList();
bool declarationList();
bool declaration();
bool IDs();
bool statementList();
bool statement();
bool compound();
bool assign();
bool ifStatement();
bool returnStatement();
bool print();
bool scan();
bool whileLoop();
bool condition();
bool relop();
bool expression();
bool expressionPrime();
bool term();
bool termPrime();
bool factor();
bool primary();
bool primaryPrime();
bool empty();

// Global variables
ifstream lexerOutput;   // input file
ofstream syntaxOutput;  // output file
vector<string> token;
vector<string> lexeme;

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

// R32. <Empty> ::=
bool empty()
{
    return true;
}

// R31. <Primary Prime> ::= ( <IDs> ) | <Empty>
bool primaryPrime()
{
    if (token[0] == "Separator" && lexeme[0] == "(")
    {
        token.erase(token.begin());
        lexeme.erase(lexeme.begin());
        if (IDs())
        {
            if (token[0] == "Separator" && lexeme[0] == ")")
            {
                token.erase(token.begin());
                lexeme.erase(lexeme.begin());
                return true;
            }
        }
    }
    else if (empty())
    {
        return true;
    }
    return false;
}

// R30. <Primary> ::= <Identifier> <Primary Prime> | <Integer> | <Identifier> ( <IDs> ) | ( <Expression> ) | <Real> | true | false
bool primary()
{
    if (token[0] == "Identifier")
    {
        token.erase(token.begin());
        lexeme.erase(lexeme.begin());
        if (primaryPrime())
        {
            return true;
        }
    }
    else if (token[0] == "Integer")
    {
        token.erase(token.begin());
        lexeme.erase(lexeme.begin());
        return true;
    }
    else if (token[0] == "Identifier")
    {
        token.erase(token.begin());
        lexeme.erase(lexeme.begin());
        if (token[0] == "Separator" && lexeme[0] == "(")
        {
            token.erase(token.begin());
            lexeme.erase(lexeme.begin());
            if (IDs())
            {
                if (token[0] == "Separator" && lexeme[0] == ")")
                {
                    token.erase(token.begin());
                    lexeme.erase(lexeme.begin());
                    return true;
                }
            }
        }
    }
    else if (token[0] == "Separator" && lexeme[0] == "(")
    {
        token.erase(token.begin());
        lexeme.erase(lexeme.begin());
        if (expression())
        {
            if (token[0] == "Separator" && lexeme[0] == ")")
            {
                token.erase(token.begin());
                lexeme.erase(lexeme.begin());
                return true;
            }
        }
    }
    else if (token[0] == "Real")
    {
        token.erase(token.begin());
        lexeme.erase(lexeme.begin());
        return true;
    }
    else if (token[0] == "Keyword" && lexeme[0] == "true")
    {
        token.erase(token.begin());
        lexeme.erase(lexeme.begin());
        return true;
    }
    else if (token[0] == "Keyword" && lexeme[0] == "false")
    {
        token.erase(token.begin());
        lexeme.erase(lexeme.begin());
        return true;
    }
    return false;
}

// R29. <Factor> ::= - <Primary> | <Primary>
bool factor()
{
    if (token[0] == "Operator" && lexeme[0] == "-")
    {
        token.erase(token.begin());
        lexeme.erase(lexeme.begin());
        if (primary())
        {
            return true;
        }
    }
    else if (primary())
    {
        return true;
    }
    return false;
}

// R28. <Term Prime> ::= * <Factor> <Term Prime> | / <Factor> <Term Prime> | <Empty>
bool termPrime()
{
    if (token[0] == "Operator" && lexeme[0] == "*")
    {
        token.erase(token.begin());
        lexeme.erase(lexeme.begin());
        if (factor())
        {
            if (termPrime())
            {
                return true;
            }
        }
    }
    else if (token[0] == "Operator" && lexeme[0] == "/")
    {
        token.erase(token.begin());
        lexeme.erase(lexeme.begin());
        if (factor())
        {
            if (termPrime())
            {
                return true;
            }
        }
    }
    else if (empty())
    {
        return true;
    }
    return false;
}

// R27. <Term> ::= <Factor> <Term Prime>
bool term()
{
    if (factor())
    {
        if (termPrime())
        {
            return true;
        }
    }
    return false;
}

// R26. <Expression Prime> ::= + <Term> <Expression Prime> | - <Term> <Expression Prime> | <Empty>
bool expressionPrime()
{
    if (token[0] == "Operator" && lexeme[0] == "+")
    {
        token.erase(token.begin());
        lexeme.erase(lexeme.begin());
        if (term())
        {
            if (expressionPrime())
            {
                return true;
            }
        }
    }
    else if (token[0] == "Operator" && lexeme[0] == "-")
    {
        token.erase(token.begin());
        lexeme.erase(lexeme.begin());
        if (term())
        {
            if (expressionPrime())
            {
                return true;
            }
        }
    }
    else if (empty())
    {
        return true;
    }
    return false;
}

// R25. <Expression> ::= <Term> <Expression Prime>
bool expression()
{
    if (term())
    {
        if (expressionPrime())
        {
            return true;
        }
    }
    return false;
}

// R24. <Relop> ::= == | != | > | < | <= | =>
bool relop()
{
    if (token[0] == "Operator" && lexeme[0] == "==")
    {
        token.erase(token.begin());
        lexeme.erase(lexeme.begin());
        return true;
    }
    else if (token[0] == "Operator" && lexeme[0] == "!=")
    {
        token.erase(token.begin());
        lexeme.erase(lexeme.begin());
        return true;
    }
    else if (token[0] == "Operator" && lexeme[0] == ">")
    {
        token.erase(token.begin());
        lexeme.erase(lexeme.begin());
        return true;
    }
    else if (token[0] == "Operator" && lexeme[0] == "<")
    {
        token.erase(token.begin());
        lexeme.erase(lexeme.begin());
        return true;
    }
    else if (token[0] == "Operator" && lexeme[0] == "<=")
    {
        token.erase(token.begin());
        lexeme.erase(lexeme.begin());
        return true;
    }
    else if (token[0] == "Operator" && lexeme[0] == ">=")
    {
        token.erase(token.begin());
        lexeme.erase(lexeme.begin());
        return true;
    }
    return false;
}

// R23. <Condition> ::= <Expression> <Relop> <Expression>
bool condition()
{
    if (expression())
    {
        if (relop())
        {
            if (expression())
            {
                return true;
            }
        }
    }
    return false;
}

// R22. <While> ::= while ( <Condition> ) <Statement> endwhile
bool whileLoop()
{
    if (token[0] == "Keyword" && lexeme[0] == "while")
    {
        token.erase(token.begin());
        lexeme.erase(lexeme.begin());
        if (token[0] == "Separator" && lexeme[0] == "(")
        {
            token.erase(token.begin());
            lexeme.erase(lexeme.begin());
            if (condition())
            {
                if (token[0] == "Separator" && lexeme[0] == ")")
                {
                    token.erase(token.begin());
                    lexeme.erase(lexeme.begin());
                    if (statement())
                    {
                        if (token[0] == "Keyword" && lexeme[0] == "endwhile")
                        {
                            token.erase(token.begin());
                            lexeme.erase(lexeme.begin());
                            return true;
                        }
                    }
                }
            }
        }
    }
    return false;
}

// R21. <Scan> ::= get ( <IDs> );
bool scan()
{
    if (token[0] == "Keyword" && lexeme[0] == "get")
    {
        token.erase(token.begin());
        lexeme.erase(lexeme.begin());
        if (token[0] == "Separator" && lexeme[0] == "(")
        {
            token.erase(token.begin());
            lexeme.erase(lexeme.begin());
            if (IDs())
            {
                if (token[0] == "Separator" && lexeme[0] == ")")
                {
                    token.erase(token.begin());
                    lexeme.erase(lexeme.begin());
                    if (token[0] == "Separator" && lexeme[0] == ";")
                    {
                        token.erase(token.begin());
                        lexeme.erase(lexeme.begin());
                        return true;
                    }
                }
            }
        }
    }
    return false;
}

// R21. <Print> ::= put ( <Expression>);
bool print()
{
    if (token[0] == "Keyword" && lexeme[0] == "put")
    {
        token.erase(token.begin());
        lexeme.erase(lexeme.begin());
        if (token[0] == "Separator" && lexeme[0] == "(")
        {
            token.erase(token.begin());
            lexeme.erase(lexeme.begin());
            if (expression())
            {
                if (token[0] == "Separator" && lexeme[0] == ")")
                {
                    token.erase(token.begin());
                    lexeme.erase(lexeme.begin());
                    if (token[0] == "Separator" && lexeme[0] == ";")
                    {
                        token.erase(token.begin());
                        lexeme.erase(lexeme.begin());
                        return true;
                    }
                }
            }
        }
    }
    return false;
}

// R19. <Return> ::= return ; | return <Expression> ;
bool returnStatement()
{
    if (token[0] == "Keyword" && lexeme[0] == "return")
    {
        token.erase(token.begin());
        lexeme.erase(lexeme.begin());
        if (token[0] == "Separator" && lexeme[0] == ";")
        {
            token.erase(token.begin());
            lexeme.erase(lexeme.begin());
            return true;
        }
        else if (expression())
        {
            if (token[0] == "Separator" && lexeme[0] == ";")
            {
                token.erase(token.begin());
                lexeme.erase(lexeme.begin());
                return true;
            }
        }
    }
    return false;
}

// R18. <If> ::= if ( <Condition> ) <Statement> fi | if ( <Condition> ) <Statement> else <Statement> fi
bool ifStatement()
{
    if (token[0] == "Keyword" && lexeme[0] == "if")
    {
        token.erase(token.begin());
        lexeme.erase(lexeme.begin());
        if (token[0] == "Separator" && lexeme[0] == "(")
        {
            token.erase(token.begin());
            lexeme.erase(lexeme.begin());
            if (condition())
            {
                if (token[0] == "Separator" && lexeme[0] == ")")
                {
                    token.erase(token.begin());
                    lexeme.erase(lexeme.begin());
                    if (statement())
                    {
                        if (token[0] == "Keyword" && lexeme[0] == "fi")
                        {
                            token.erase(token.begin());
                            lexeme.erase(lexeme.begin());
                            return true;
                        }
                        else if (token[0] == "Keyword" && lexeme[0] == "else")
                        {
                            token.erase(token.begin());
                            lexeme.erase(lexeme.begin());
                            if (statement())
                            {
                                if (token[0] == "Keyword" && lexeme[0] == "fi")
                                {
                                    token.erase(token.begin());
                                    lexeme.erase(lexeme.begin());
                                    return true;
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    return false;
}

// R17. <Assign> ::= <Identifier> = <Expression> ;
bool assign()
{
    if (token[0] == "Identifier")
    {
        token.erase(token.begin());
        lexeme.erase(lexeme.begin());
        if (token[0] == "Operator" && lexeme[0] == "=")
        {
            token.erase(token.begin());
            lexeme.erase(lexeme.begin());
            if (expression())
            {
                if (token[0] == "Separator" && lexeme[0] == ";")
                {
                    token.erase(token.begin());
                    lexeme.erase(lexeme.begin());
                    return true;
                }
            }
        }
    }
    return false;
}

// R16. <Compound> ::= { <Statement List> }
bool compound()
{
    if (token[0] == "Separator" && lexeme[0] == "{")
    {
        token.erase(token.begin());
        lexeme.erase(lexeme.begin());
        if (statementList())
        {
            if (token[0] == "Separator" && lexeme[0] == "}")
            {
                token.erase(token.begin());
                lexeme.erase(lexeme.begin());
                return true;
            }
        }
    }
    return false;
}

// R15. <Statement> ::= <Compound> | <Assign> | <If> | <Return> | <Print> | <Scan> | <While>
bool statement()
{
    if (compound())
    {
        return true;
    }
    else if (assign())
    {
        return true;
    }
    else if (ifStatement())
    {
        return true;
    }
    else if (returnStatement())
    {
        return true;
    }
    else if (print())
    {
        return true;
    }
    else if (scan())
    {
        return true;
    }
    else if (whileLoop())
    {
        return true;
    }
    return false;
}

// R14. <Statement List> ::= <Statement> | <Statement> <Statement List>
bool statementList()
{
    if (statement())
    {
        if (statementList())
        {
            return true;
        }
    }
    return false;
}

// R13. <IDs> ::= <Identifier> | <Identifier>, <IDs>
bool IDs()
{
    if (token[0] == "Identifier")
    {
        token.erase(token.begin());
        lexeme.erase(lexeme.begin());
        if (token[0] == "Separator" && lexeme[0] == ",")
        {
            token.erase(token.begin());
            lexeme.erase(lexeme.begin());
            if (IDs())
            {
                return true;
            }
        }
        else if (empty())
        {
            return true;
        }
    }
    return false;
}

// R12. <Declaration> ::= <Qualifier > <IDs>
bool declaration()
{
    if (qualifier())
    {
        if (IDs())
        {
            return true;
        }
    }
    return false;
}

// R11. <Declaration List> := <Declaration> ; | <Declaration> ; <Declaration List>
bool declarationList()
{
    if (declaration())
    {
        if (token[0] == "Separator" && lexeme[0] == ";")
        {
            token.erase(token.begin());
            lexeme.erase(lexeme.begin());
            if (declarationList())
            {
                return true;
            }
        }
    }
    return false;
}

// R10. <Opt Declaration List> ::= <Declaration List> | <Empty>
bool optDeclarationList()
{
    if (declarationList())
    {
        return true;
    }
    else if (empty())
    {
        return true;
    }
    return false;
}

// R9. <Body> ::= { < Statement List> }
bool body()
{
    if (token[0] == "Separator" && lexeme[0] == "{")
    {
        token.erase(token.begin());
        lexeme.erase(lexeme.begin());
        if (statementList())
        {
            if (token[0] == "Separator" && lexeme[0] == "}")
            {
                token.erase(token.begin());
                lexeme.erase(lexeme.begin());
                return true;
            }
        }
    }
    return false;
}

// R8. <Qualifier> ::= int | bool | real
bool qualifier()
{
    if (token[0] == "Keyword" && lexeme[0] == "int")
    {
        token.erase(token.begin());
        lexeme.erase(lexeme.begin());
        return true;
    }
    else if (token[0] == "Keyword" && lexeme[0] == "bool")
    {
        token.erase(token.begin());
        lexeme.erase(lexeme.begin());
        return true;
    }
    else if (token[0] == "Keyword" && lexeme[0] == "real")
    {
        token.erase(token.begin());
        lexeme.erase(lexeme.begin());
        return true;
    }
    return false;
}

// R7. <Parameter> ::= <IDs > <Qualifier>
bool parameter()
{
    if (IDs())
    {
        if (qualifier())
        {
            return true;
        }
    }
    return false;
}

// R6. <Parameter List> ::= <Parameter> | <Parameter> , <Parameter List>
bool parameterList()
{
    if (parameter())
    {
        if (token[0] == "Separator" && lexeme[0] == ",")
        {
            token.erase(token.begin());
            lexeme.erase(lexeme.begin());
            if (parameterList())
            {
                return true;
            }
        }
        else if (empty())
        {
            return true;
        }
    }
    return false;
}

// R5. <Opt Parameter List> ::= <Parameter List> | <Empty>
bool optParameterList()
{
    if (parameterList())
    {
        return true;
    }
    else if (empty())
    {
        return true;
    }
    return false;
}

// R4. <Function> ::= function <Identifier> ( <Opt Parameter List> ) <Opt Declaration List> <Body>
bool function()
{
    if (token[0] == "Keyword" && lexeme[0] == "function")
    {
        token.erase(token.begin());
        lexeme.erase(lexeme.begin());
        if (token[0] == "Identifier")
        {
            token.erase(token.begin());
            lexeme.erase(lexeme.begin());
            if (token[0] == "Separator" && lexeme[0] == "(")
            {
                token.erase(token.begin());
                lexeme.erase(lexeme.begin());
                if (optParameterList())
                {
                    if (token[0] == "Separator" && lexeme[0] == ")")
                    {
                        token.erase(token.begin());
                        lexeme.erase(lexeme.begin());
                        if (optDeclarationList())
                        {
                            if (body())
                            {
                                return true;
                            }
                        }
                    }
                }
            }
        }
    }
    return false;
}

// R3. <Function Definitions> ::= <Function> | <Function> <Function Definitions>
bool functionDefinitions()
{
    if (function())
    {
        if (functionDefinitions())
        {
            return true;
        }
    }
    return false;
}

// R2. <Opt Function Definitions> ::= <Function Definitions> | <Empty>
bool optFunctionDefinitions()
{
    if (functionDefinitions())
    {
        return true;
    }
    else if (empty())
    {
        return true;
    }
    return false;
}

// R1. <Rat23S> ::= <Opt Function Definitions> # <Opt Declaration List> # <Statement List>
bool rat23S()
{
    if (optFunctionDefinitions())
    {
        if (token[0] == "Separator" && lexeme[0] == "#")
        {
            token.erase(token.begin());
            lexeme.erase(lexeme.begin());
            if (optDeclarationList())
            {
                if (token[0] == "Separator" && lexeme[0] == "#")
                {
                    token.erase(token.begin());
                    lexeme.erase(lexeme.begin());
                    if (statementList())
                    {
                        return true;
                    }
                }
            }
        }
    }
    return false;
}

// main program
void syntax()
{
    if (rat23S())
    {
        cout << "Syntax is correct!" << endl;
    }
    else
    {
        cout << "Syntax error!" << endl;
    }
}

#endif