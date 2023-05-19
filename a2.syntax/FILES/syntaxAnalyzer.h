/*
R1. <Rat23S> ::= <Opt Function Definitions> # <Opt Declaration List> # <Statement List> 
R2. <Opt Function Definitions> ::= <Function Definitions> | <Empty>
R3. <Function Definitions> ::= <Function> | <Function> <Function Definitions> 
R4. <Function> ::= function <identifier> ( <Opt Parameter List> ) <Opt Declaration List> <Body>
R5. <Opt Parameter List> ::= <Parameter List> | <Empty>
R6. <Parameter List> ::= <Parameter> | <Parameter> , <Parameter List>
R7. <Parameter> ::= <IDs > <Qualifier> 
R8. <Qualifier> ::= int | bool | real 
R9. <Body> ::= { < Statement List> }
R10. <Opt Declaration List> ::= <Declaration List> | <Empty>
R11. <Declaration List> := <Declaration> ; | <Declaration> ; <Declaration List>
R12. <Declaration> ::= <Qualifier > <IDs> 
R13. <IDs> ::= <identifier> | <identifier>, <IDs>
R14. <Statement List> ::= <Statement> | <Statement> <Statement List>
R15. <Statement> ::= <Compound> | <Assign> | <If> | <Return> | <Print> | <Scan> | <While> 
R16. <Compound> ::= { <Statement List> } 
R17. <Assign> ::= <identifier> = <Expression> ;
R18. <If> ::= if ( <Condition> ) <Statement> fi | if ( <Condition> ) <Statement> else <Statement> fi
R19. <Return> ::= return ; | return <Expression> ;
R20. <Print> ::= put ( <Expression>);
R21. <Scan> ::= get ( <IDs> );
R22. <While> ::= while ( <Condition> ) <Statement> endwhile
R23. <Condition> ::= <Expression> <Relop> <Expression>
R24. <Relop> ::= == | != | > | < | <= | => 
R25. <Expression> ::= <Expression> + <Term> | <Expression> - <Term> | <Term>    // use new rule below
R26. <Term> ::= <Term> * <Factor> | <Term> / <Factor> | <Factor>                // use new rule below
R27. <Factor> ::= - <Primary> | <Primary>
R28. <Primary> ::= <identifier> | <Integer> | <identifier> ( <IDs> ) | ( <Expression> ) | <Real> | true | false 
R29. <Empty> ::= <epsilon>

Removed Left Recursion / Backtracking:

R25. <Expression> ::= <Term> <ExpressionPrime>
R25.1. <ExpressionPrime> ::= + <Term> <ExpressionPrime> | - <Term> <ExpressionPrime> | <Empty>
R26. <Term> ::= <Factor> <TermPrime>
R26.1. <TermPrime> ::= * <Factor> <TermPrime> | / <Factor> <TermPrime> | <Empty>
*/
#ifndef SYNTAXANALYZER_H
#define SYNTAXANALYZER_H

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

using namespace std;

// Function prototypes
void openSyntaxFile();
void closeSyntaxFile();
void tokenListHelper(ifstream& lexerOutput);
// main syntax analyzer function prototypes
void syntaxAnalyzer();  // main syntax analyzer function

// Global variables
ifstream lexerOutput;   // input file
ofstream syntaxOutput;  // output file for the syntax analyzer
string syntaxOutputFile; // output file for the syntax analyzer

vector<TokenType> tokenList; 
TokenType currentToken; // current token
int tokenCounter = 0;   // token counter
bool printSwitch = true;

// Get tokens from vector<TokenType> parseTokens(ifstream &testInput) function in lexer.h, which will be used in the syntax analyzer
vector<TokenType> tokens = parseTokens(lexerOutput);

// Syntax rule function prototypes

class SA
{
public:
void Rat23S();
void OptFunctionDefinitions();
void FunctionDefinitions();
void Function();
void OptParameterList();
void ParameterList();
void Parameter();
void Qualifier();
void Body();
void OptDeclarationList();
void DeclarationList();
void Declaration();
void IDs();
void StatementList();
void Statement();
void Compound();
void Assign();
void If();
void Return();
void Print();
void Scan();
void While();
void Condition();
void Relop();
void Expression();
void Term();
void Factor();
void Primary();
void Empty();
void GetNextToken();
// left recursion / backtracking functions
void ExpressionPrime();
void TermPrime();
};

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

// main syntax analyzer functions

// main syntax analyzer function 
void syntaxAnalyzer()
{
    ifstream lexerOutput("lexerOutput.txt");
    
    if (!lexerOutput.is_open())
    {
        cout << "Error opening lexer output file" << endl;
        return;
    }

    tokenListHelper(lexerOutput);
    openSyntaxFile();
    SA sa;
    sa.Rat23S();
    closeSyntaxFile();

    lexerOutput.close();
}

// helper function

void tokenListHelper(ifstream& lexerOutput)
{
    tokenList = parseTokens(lexerOutput);
}

void SA::GetNextToken()
{
    if (tokenCounter < tokenList.size())
    {
        currentToken = tokenList[tokenCounter];
        if (printSwitch)
        {
            syntaxOutput << "\nToken: " << left << setw(20) << currentToken.token << left << setw(8) << "Lexeme: " << left << setw(20) << currentToken.lexeme << endl;
        }
        tokenCounter++;
    }
}

// Syntax rules

void SA::Rat23S()
{
    GetNextToken();

    if (printSwitch)
    {
        syntaxOutput << "<Rat23S> ::= <Opt Function Definitions> # <Opt Declaration List> # <Statement List>" << endl;
        cout << "<Rat23S> ::= <Opt Function Definitions> # <Opt Declaration List> # <Statement List>" << endl;
    }

    OptFunctionDefinitions();

    if (currentToken.lexeme == "#")
    {
        GetNextToken();
        OptDeclarationList();
        StatementList();
        syntaxOutput << "Syntax Accepted" << endl;
        cout << "Syntax Accepted" << endl;
    }
    else
    {
        syntaxOutput << "Syntax error; Expected '#' before '" << currentToken.lexeme << "'" << endl;
        cout << "Syntax error; Expected '#' before '" << currentToken.lexeme << "'" << endl;
    }
}

void SA::OptFunctionDefinitions()
{
    if (printSwitch)
    {
        syntaxOutput << "<Opt Function Definitions> ::= <Function Definitions> | <Empty>" << endl;
        cout << "<Opt Function Definitions> ::= <Function Definitions> | <Empty>" << endl;
    }
    if (currentToken.lexeme == "function")
    {
        FunctionDefinitions();
    }
    else if (currentToken.lexeme == "#")
    {
        Empty();
    }
    else
    {
        syntaxOutput << "Syntax error; Expected 'function' or '#' before '" << currentToken.lexeme << "'" << endl;
        cout << "Syntax error; Expected 'function' or '#' before '" << currentToken.lexeme << "'" << endl;
    }
}

void SA::FunctionDefinitions()
{
    if (printSwitch)
    {
        syntaxOutput << "<Function Definitions> ::= <Function> | <Function> <Function Definitions>" << endl;
        cout << "<Function Definitions> ::= <Function> | <Function> <Function Definitions>" << endl;
    }
    while (currentToken.lexeme == "function")
    {
        Function();
    }
}

void SA::Function()
{
    if (printSwitch)
    {
        syntaxOutput << "<Function> ::= function <identifier> ( <Opt Parameter List> ) <Opt Declaration List> <Body>" << endl;
    }
    GetNextToken();
    if (currentToken.token == "identifier")
    {
        GetNextToken();
        if (currentToken.lexeme == "(")
        {
            GetNextToken();
            OptParameterList();
            if (currentToken.lexeme == ")")
            {
                GetNextToken();
                OptDeclarationList();
                Body();
            }
            else
            {
                syntaxOutput << "Syntax error; Expected ')' before '" << currentToken.lexeme << "'" << endl;
                cout << "Syntax error; Expected ')' before '" << currentToken.lexeme << "'" << endl;
                exit(1);
            }
        }
        else
        {
            syntaxOutput << "Syntax error; Expected '(' before '" << currentToken.lexeme << "'" << endl;
            cout << "Syntax error; Expected '(' before '" << currentToken.lexeme << "'" << endl;
            exit(1);
        }
    }
    else
    {
        syntaxOutput << "Syntax error; Expected an identifier before '" << currentToken.lexeme << "'" << endl;
        cout << "Syntax error; Expected an identifier before '" << currentToken.lexeme << "'" << endl;
        exit(1);
    }
}

void SA::OptParameterList()
{
    if (printSwitch)
    {
        syntaxOutput << "<Opt Parameter List> ::= <Parameter List> | <Empty>" << endl;
        cout << "<Opt Parameter List> ::= <Parameter List> | <Empty>" << endl;
    }
    if (currentToken.token == "identifier")
    {
        ParameterList();
    }
    else if (currentToken.lexeme == ")")
    {
        Empty();
    }
    else
    {
        syntaxOutput << "Syntax error; Expected an identifier or ')' before '" << currentToken.lexeme << "'" << endl;
        cout << "Syntax error; Expected an identifier or ')' before '" << currentToken.lexeme << "'" << endl;
        exit(1);
    }
}

void SA::ParameterList()
{
    if (printSwitch)
    {
        syntaxOutput << "<Parameter List> ::= <Parameter> | <Parameter> , <Parameter List>" << endl;
        cout << "<Parameter List> ::= <Parameter> | <Parameter> , <Parameter List>" << endl;
    }
    if (currentToken.token == "identifier")
    {
        Parameter();
        if (currentToken.lexeme == ",")
        {
            GetNextToken();
            ParameterList();
        }
    }
    else
    {
        syntaxOutput << "Syntax error; Expected an identifier before '" << currentToken.lexeme << "'" << endl;
        cout << "Syntax error; Expected an identifier before '" << currentToken.lexeme << "'" << endl;
        exit(1);
    }
}

void SA::Parameter()
{
    if (printSwitch)
    {
        syntaxOutput << "<Parameter> ::= <IDs > : <Qualifier>" << endl;
        cout << "<Parameter> ::= <IDs > : <Qualifier>" << endl;
    }
    IDs();
    if (currentToken.lexeme == ":")
    {
        GetNextToken();
        Qualifier();
    }
    else
    {
        syntaxOutput << "Syntax error; Expected ':' before '" << currentToken.lexeme << "'" << endl;
        cout << "Syntax error; Expected ':' before '" << currentToken.lexeme << "'" << endl;
        exit(1);
    }
}

void SA::Qualifier()
{
    if (printSwitch)
    {
        syntaxOutput << "<Qualifier> ::= int | boolean | real" << endl;
        cout << "<Qualifier> ::= int | boolean | real" << endl;
    }
    if (currentToken.lexeme == "int" || currentToken.lexeme == "boolean" || currentToken.lexeme == "real")
    {
        GetNextToken();
    }
    else
    {
        syntaxOutput << "Syntax error; Expected 'int', 'boolean', or 'real' before '" << currentToken.lexeme << "'" << endl;
        cout << "Syntax error; Expected 'int', 'boolean', or 'real' before '" << currentToken.lexeme << "'" << endl;
        exit(1);
    }
}

void SA::Body()
{
    if (printSwitch)
    {
        syntaxOutput << "<Body> ::= { < Statement List> }" << endl;
        cout << "<Body> ::= { < Statement List> }" << endl;
    }
    if (currentToken.lexeme == "{")
    {
        GetNextToken();
        StatementList();
        if (currentToken.lexeme == "}")
        {
            GetNextToken();
        }
        else
        {
            syntaxOutput << "Syntax error; Expected '}' before '" << currentToken.lexeme << "'" << endl;
            cout << "Syntax error; Expected '}' before '" << currentToken.lexeme << "'" << endl;
            exit(1);
        }
    }
    else
    {
        syntaxOutput << "Syntax error; Expected '{' before '" << currentToken.lexeme << "'" << endl;
        cout << "Syntax error; Expected '{' before '" << currentToken.lexeme << "'" << endl;
        exit(1);
    }
}

void SA::OptDeclarationList()
{
    if (printSwitch)
    {
        syntaxOutput << "<Opt Declaration List> ::= <Declaration List> | <Empty>" << endl;
        cout << "<Opt Declaration List> ::= <Declaration List> | <Empty>" << endl;
    }
    if (currentToken.lexeme == "int" || currentToken.lexeme == "boolean" || currentToken.lexeme == "real")
    {
        DeclarationList();
    }
    else if (currentToken.lexeme == "{")
    {
        Empty();
    }
    else
    {
        syntaxOutput << "Syntax error; Expected 'int', 'boolean', 'real', or '{' before '" << currentToken.lexeme << "'" << endl;
        cout << "Syntax error; Expected 'int', 'boolean', 'real', or '{' before '" << currentToken.lexeme << "'" << endl;
        exit(1);
    }
}

void SA::DeclarationList()
{
    if (printSwitch)
    {
        syntaxOutput << "<Declaration List> := <Declaration> ; | <Declaration> ; <Declaration List>" << endl;
        cout << "<Declaration List> := <Declaration> ; | <Declaration> ; <Declaration List>" << endl;
    }
    Declaration();
    if (currentToken.lexeme == ";")
    {
        GetNextToken();
        if (currentToken.lexeme == "int" || currentToken.lexeme == "boolean" || currentToken.lexeme == "real")
        {
            DeclarationList();
        }
    }
    else
    {
        syntaxOutput << "Syntax error; Expected ';' before '" << currentToken.lexeme << "'" << endl;
        cout << "Syntax error; Expected ';' before '" << currentToken.lexeme << "'" << endl;
        exit(1);
    }
}

void SA::Declaration()
{
    if (printSwitch)
    {
        syntaxOutput << "<Declaration> ::= <Qualifier > <IDs>" << endl;
        cout << "<Declaration> ::= <Qualifier > <IDs>" << endl;
    }
    Qualifier();
    IDs();
}

void SA::IDs()
{
    if (printSwitch)
    {
        syntaxOutput << "<IDs> ::= <identifier> | <identifier>, <IDs>" << endl;
        cout << "<IDs> ::= <identifier> | <identifier>, <IDs>" << endl;
    }
    if (currentToken.token == "identifier")
    {
        GetNextToken();
        if (currentToken.lexeme == ",")
        {
            GetNextToken();
            IDs();
        }
    }
    else
    {
        syntaxOutput << "Syntax error; Expected an identifier before '" << currentToken.lexeme << "'" << endl;
        cout << "Syntax error; Expected an identifier before '" << currentToken.lexeme << "'" << endl;
        exit(1);
    }
}

void SA::StatementList()
{
    if (printSwitch)
    {
        syntaxOutput << "<Statement List> ::= <Statement> | <Statement> <Statement List>" << endl;
        cout << "<Statement List> ::= <Statement> | <Statement> <Statement List>" << endl;
    }
    while (currentToken.lexeme == "if" || currentToken.lexeme == "return" || currentToken.lexeme == "put" || currentToken.lexeme == "get" || currentToken.token == "identifier" || currentToken.lexeme == "{")
    {
        Statement();
    }
}

void SA::Statement()
{
    if (printSwitch)
    {
        syntaxOutput << "<Statement> ::= <Compound> | <Assign> | <If> | <Return> | <Print> | <Scan>" << endl;
        cout << "<Statement> ::= <Compound> | <Assign> | <If> | <Return> | <Print> | <Scan>" << endl;
    }
    if (currentToken.lexeme == "{")
    {
        Compound();
    }
    else if (currentToken.token == "identifier")
    {
        Assign();
    }
    else if (currentToken.lexeme == "if")
    {
        If();
    }
    else if (currentToken.lexeme == "return")
    {
        Return();
    }
    else if (currentToken.lexeme == "put")
    {
        Print();
    }
    else if (currentToken.lexeme == "get")
    {
        Scan();
    }
    else if (currentToken.lexeme == "function")
    {
        Function();
    }
    else if (currentToken.lexeme == "while")
    {
        While();
    }
    else
    {
        syntaxOutput << "Syntax error; Expected '{', an identifier, 'if', 'return', 'put', 'get', 'function', or 'while' before '" << currentToken.lexeme << "'" << endl;
        cout << "Syntax error; Expected '{', an identifier, 'if', 'return', 'put', 'get', 'function', or 'while' before '" << currentToken.lexeme << "'" << endl;
        exit(1);
    }
}

void SA::Compound()
{
    if (printSwitch)
    {
        syntaxOutput << "<Compound> ::= { <Statement List> }" << endl;
        cout << "<Compound> ::= { <Statement List> }" << endl;
    }
    if (currentToken.lexeme == "{")
    {
        GetNextToken();
        StatementList();
        if (currentToken.lexeme == "}")
        {
            GetNextToken();
        }
        else
        {
            syntaxOutput << "Syntax error; Expected '}' before '" << currentToken.lexeme << "'" << endl;
            cout << "Syntax error; Expected '}' before '" << currentToken.lexeme << "'" << endl;
            exit(1);
        }
    }
    else
    {
        syntaxOutput << "Syntax error; Expected '{' before '" << currentToken.lexeme << "'" << endl;
        cout << "Syntax error; Expected '{' before '" << currentToken.lexeme << "'" << endl;
        exit(1);
    }
}

void SA::Assign()
{
    if (printSwitch)
    {
        syntaxOutput << "<Assign> ::= <identifier> = <Expression> ;" << endl;
        cout << "<Assign> ::= <identifier> = <Expression> ;" << endl;
    }
    if (currentToken.token == "identifier")
    {
        GetNextToken();
        if (currentToken.lexeme == "=")
        {
            GetNextToken();
            Expression();
            if (currentToken.lexeme == ";")
            {
                GetNextToken();
            }
            else
            {
                syntaxOutput << "Syntax error; Expected ';' before '" << currentToken.lexeme << "'" << endl;
                cout << "Syntax error; Expected ';' before '" << currentToken.lexeme << "'" << endl;
                exit(1);
            }
        }
        else if (currentToken.lexeme == ";")
        {
            GetNextToken();
        }
        else
        {
            syntaxOutput << "Syntax error; Expected '=' or ';' before '" << currentToken.lexeme << "'" << endl;
            cout << "Syntax error; Expected '=' or ';' before '" << currentToken.lexeme << "'" << endl;
            exit(1);
        }
    }
    else
    {
        syntaxOutput << "Syntax error; Expected an identifier before '" << currentToken.lexeme << "'" << endl;
        cout << "Syntax error; Expected an identifier before '" << currentToken.lexeme << "'" << endl;
        exit(1);
    }
}

void SA::If()
{
    if (printSwitch)
    {
        syntaxOutput << "<If> ::= if ( <Condition> ) <Statement> fi | if ( <Condition> ) <Statement> else <Statement> fi" << endl;
        cout << "<If> ::= if ( <Condition> ) <Statement> fi | if ( <Condition> ) <Statement> else <Statement> fi" << endl;
    }
    if (currentToken.lexeme == "if")
    {
        GetNextToken();
        if (currentToken.lexeme == "(")
        {
            GetNextToken();
            Condition();
            if (currentToken.lexeme == ")")
            {
                GetNextToken();
                Statement();
                if (currentToken.lexeme == "fi")
                {
                    GetNextToken();
                }
                else if (currentToken.lexeme == "else")
                {
                    GetNextToken();
                    Statement();
                    if (currentToken.lexeme == "fi")
                    {
                        GetNextToken();
                    }
                    else
                    {
                        syntaxOutput << "Syntax error; Expected 'fi' before '" << currentToken.lexeme << "'" << endl;
                        cout << "Syntax error; Expected 'fi' before '" << currentToken.lexeme << "'" << endl;
                        exit(1);
                    }
                }
                else
                {
                    syntaxOutput << "Syntax error; Expected 'fi' or 'else' before '" << currentToken.lexeme << "'" << endl;
                    cout << "Syntax error; Expected 'fi' or 'else' before '" << currentToken.lexeme << "'" << endl;
                    exit(1);
                }
            }
            else
            {
                syntaxOutput << "Syntax error; Expected ')' before '" << currentToken.lexeme << "'" << endl;
                cout << "Syntax error; Expected ')' before '" << currentToken.lexeme << "'" << endl;
                exit(1);
            }
        }
        else
        {
            syntaxOutput << "Syntax error; Expected '(' before '" << currentToken.lexeme << "'" << endl;
            cout << "Syntax error; Expected '(' before '" << currentToken.lexeme << "'" << endl;
            exit(1);
        }
    }
}

void SA::Return()
{
    if (printSwitch)
    {
        syntaxOutput << "<Return> ::= return ; | return <Expression> ;" << endl;
        cout << "<Return> ::= return ; | return <Expression> ;" << endl;
    }
    GetNextToken();
    if (currentToken.lexeme == ";")
    {
        GetNextToken();
    }
    else
    {
        Expression();
        if (currentToken.lexeme == ";")
        {
            GetNextToken();
        }
        else
        {
            syntaxOutput << "Syntax error; Expected ';' before '" << currentToken.lexeme << "'" << endl;
            cout << "Syntax error; Expected ';' before '" << currentToken.lexeme << "'" << endl;
            exit(1);
        }
    }
}

void SA::Print()
{
    if (printSwitch)
    {
        syntaxOutput << "<Print> ::= put ( <Expression>);" << endl;
        cout << "<Print> ::= put ( <Expression>);" << endl;
    }
    GetNextToken();
    if (currentToken.lexeme == "(")
    {
        GetNextToken();
        Expression();
        if (currentToken.lexeme == ")")
        {
            GetNextToken();
            if (currentToken.lexeme == ";")
            {
                GetNextToken();
            }
            else
            {
                syntaxOutput << "Syntax error; Expected ';' before '" << currentToken.lexeme << "'" << endl;
                cout << "Syntax error; Expected ';' before '" << currentToken.lexeme << "'" << endl;
                exit(1);
            }
        }
        else
        {
            syntaxOutput << "Syntax error; Expected ')' before '" << currentToken.lexeme << "'" << endl;
            cout << "Syntax error; Expected ')' before '" << currentToken.lexeme << "'" << endl;
            exit(1);
        }
    }
    else
    {
        syntaxOutput << "Syntax error; Expected '(' before '" << currentToken.lexeme << "'" << endl;
        cout << "Syntax error; Expected '(' before '" << currentToken.lexeme << "'" << endl;
        exit(1);
    }
}

void SA::Scan()
{
    if (printSwitch)
    {
        syntaxOutput << "<Scan> ::= get ( <IDs> );" << endl;
        cout << "<Scan> ::= get ( <IDs> );" << endl;
    }
    GetNextToken();
    if (currentToken.lexeme == "(")
    {
        GetNextToken();
        IDs();
        if (currentToken.lexeme == ")")
        {
            GetNextToken();
            if (currentToken.lexeme == ";")
            {
                GetNextToken();
            }
            else
            {
                syntaxOutput << "Syntax error; Expected ';' before '" << currentToken.lexeme << "'" << endl;
                cout << "Syntax error; Expected ';' before '" << currentToken.lexeme << "'" << endl;
                exit(1);
            }
        }
        else
        {
            syntaxOutput << "Syntax error; Expected ')' before '" << currentToken.lexeme << "'" << endl;
            cout << "Syntax error; Expected ')' before '" << currentToken.lexeme << "'" << endl;
            exit(1);
        }
    }
    else
    {
        syntaxOutput << "Syntax error; Expected '(' before '" << currentToken.lexeme << "'" << endl;
        cout << "Syntax error; Expected '(' before '" << currentToken.lexeme << "'" << endl;
        exit(1);
    }
}

void SA::While()
{
    if (printSwitch)
    {
        syntaxOutput << "<While> ::= while ( <Condition> ) <Statement> endwhile" << endl;
        cout << "<While> ::= while ( <Condition> ) <Statement> endwhile" << endl;
    }
    GetNextToken();
    if (currentToken.lexeme == "(")
    {
        GetNextToken();
        Condition();
        if (currentToken.lexeme == ")")
        {
            GetNextToken();
            Statement();
            if (currentToken.lexeme == "endwhile")
            {
                GetNextToken();
            }
            else
            {
                syntaxOutput << "Syntax error; Expected 'endwhile' before '" << currentToken.lexeme << "'" << endl;
                cout << "Syntax error; Expected 'endwhile' before '" << currentToken.lexeme << "'" << endl;
                exit(1);
            }
        }
        else
        {
            syntaxOutput << "Syntax error; Expected ')' before '" << currentToken.lexeme << "'" << endl;
            cout << "Syntax error; Expected ')' before '" << currentToken.lexeme << "'" << endl;
            exit(1);
        }
    }
    else
    {
        syntaxOutput << "Syntax error; Expected '(' before '" << currentToken.lexeme << "'" << endl;
        cout << "Syntax error; Expected '(' before '" << currentToken.lexeme << "'" << endl;
        exit(1);
    }
}

void SA::Condition()
{
    if (printSwitch)
    {
        syntaxOutput << "<Condition> ::= <Expression> <Relop> <Expression>" << endl;
        cout << "<Condition> ::= <Expression> <Relop> <Expression>" << endl;
    }
    Expression();
    Relop();
    Expression();
}

void SA::Relop()
{
    if (printSwitch)
    {
        syntaxOutput << "<Relop> ::= == | != | > | < | <= | =>" << endl;
        cout << "<Relop> ::= == | != | > | < | <= | =>" << endl;
    }
    if (currentToken.lexeme == "==" | currentToken.lexeme == "!=" | currentToken.lexeme == ">" | currentToken.lexeme == "<" | currentToken.lexeme == "<=" | currentToken.lexeme == "=>")
    {
        GetNextToken();
    }
    else
    {
        syntaxOutput << "Syntax error; Expected '==' | '!=' | '>' | '<' | '<=' | '=>' before '" << currentToken.lexeme << "'" << endl;
        cout << "Syntax error; Expected '==' | '!=' | '>' | '<' | '<=' | '=>' before '" << currentToken.lexeme << "'" << endl;
        exit(1);
    }
}

void SA::Expression()
{
    if (printSwitch)
    {
        syntaxOutput << "<Expression> ::= <Term> <Expression Prime>" << endl;
        cout << "<Expression> ::= <Term> <Expression Prime>" << endl;
    }
    Term();
    ExpressionPrime();
}

void SA::Term()
{
    if (printSwitch)
    {
        syntaxOutput << "<Term> ::= <Factor> <Term Prime>" << endl;
        cout << "<Term> ::= <Factor> <Term Prime>" << endl;
    }
    Factor();
    TermPrime();
}

void SA::Factor()
{
    if (printSwitch)
    {
        syntaxOutput << "<Factor> ::= - <Primary> | <Primary>" << endl;
        cout << "<Factor> ::= - <Primary> | <Primary>" << endl;
    }
    if (currentToken.lexeme == "-")
    {
        GetNextToken();
    }
    Primary();
}

void SA::Primary()
{
    if (printSwitch)
    {
        syntaxOutput << "<Primary> ::= <identifier> | <Integer> | <identifier> ( <IDs> ) | ( <Expression> ) | <Real> | true | false" << endl;
        cout << "<Primary> ::= <identifier> | <Integer> | <identifier> ( <IDs> ) | ( <Expression> ) | <Real> | true | false" << endl;
    }
    if (currentToken.token == "identifier")
    {
        GetNextToken();
        if (currentToken.lexeme == "(")
        {
            GetNextToken();
            IDs();
            if (currentToken.lexeme == ")")
            {
                GetNextToken();
            }
            else
            {
                syntaxOutput << "Syntax error; Expected ')' before '" << currentToken.lexeme << "'" << endl;
                cout << "Syntax error; Expected ')' before '" << currentToken.lexeme << "'" << endl;
                exit(1);
            }
        }
    }
    else if (currentToken.token == "Integer")
    {
        GetNextToken();
    }
    else if (currentToken.lexeme == "(")
    {
        GetNextToken();
        Expression();
        if (currentToken.lexeme == ")")
        {
            GetNextToken();
        }
        else
        {
            syntaxOutput << "Syntax error; Expected ')' before '" << currentToken.lexeme << "'" << endl;
            cout << "Syntax error; Expected ')' before '" << currentToken.lexeme << "'" << endl;
            exit(1);
        }
    }
    else if (currentToken.token == "Real")
    {
        GetNextToken();
    }
    else if (currentToken.lexeme == "true" || currentToken.lexeme == "false")
    {
        GetNextToken();
    }
    else
    {
        syntaxOutput << "Syntax error; Expected 'identifier' or 'Integer' or 'identifier' or '(' or 'Real' or 'true' or 'false' before '" << currentToken.lexeme << "'" << endl;
        cout << "Syntax error; Expected 'identifier' or 'Integer' or 'identifier' or '(' or 'Real' or 'true' or 'false' before '" << currentToken.lexeme << "'" << endl;
        exit(1);
    }
}

void SA::Empty()
{
    if (printSwitch)
    {
        syntaxOutput << "<Empty> ::= epsilon" << endl;
        cout << "<Empty> ::= epsilon" << endl;
    }
}

void SA::ExpressionPrime()
{
    if (printSwitch)
    {
        syntaxOutput << "<Expression Prime> ::= + <Term> <Expression Prime> | - <Term> <Expression Prime> | <Empty> " << endl;
        cout << "<Expression Prime> ::= + <Term> <Expression Prime> | - <Term> <Expression Prime> | <Empty> " << endl;
    }
    if (currentToken.lexeme == "+" || currentToken.lexeme == "-")
    {
        GetNextToken();
        Term();
        ExpressionPrime();
    }
    else
    {
        Empty();
    }
}

void SA::TermPrime()
{
    if (printSwitch)
    {
        syntaxOutput << "<Term Prime> ::= * <Factor> <Term Prime> | / <Factor> <Term Prime> | <Empty>" << endl;
        cout << "<Term Prime> ::= * <Factor> <Term Prime> | / <Factor> <Term Prime> | <Empty>" << endl;
    }
    if (currentToken.lexeme == "*" || currentToken.lexeme == "/")
    {
        GetNextToken();
        Factor();
        TermPrime();
    }
    else
    {
        Empty();
    }
}

#endif