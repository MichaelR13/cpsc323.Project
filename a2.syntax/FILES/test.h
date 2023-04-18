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
    
    Token: seperator Lexeme: ;
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

using namespace std;

// Function prototypes
void openSyntaxFile();
void closeSyntaxFile();
void readToken();
void tester();
void syntaxAnalyzer();  // main syntax analyzer function

// Helper functions
void setTokCounter(int num);
int getTokCounter();
vector <string> getTok();
vector <string> getNextTok();

// Recursive descent parser functions
bool Aprime();
bool A();
bool B();
bool C();
bool D();
bool E();
bool F();
bool G();
bool H();
bool I();
bool J();
bool K();
bool L();
bool M();
bool N();
bool O();
bool P();
bool Q();
bool R();
bool S();
bool T();
bool U();
bool V();
bool W();
bool X();
bool Y();
bool Yprime();
bool Z();
bool Zprime();
bool AA();
bool BB();


// Global variables
ifstream lexerOutput;   // input file
ofstream syntaxOutput;  // output file
vector<string> token;
vector<string> lexeme;
// vector<vector<string>> tokenLexeme;

int tokCounter = -1;    // counter for the token vector

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
/*
void tokenLexemeVector()
{
    // add the token and lexeme vectors to a 2D vector (tokenLexeme)
    for (int i = 0; i < token.size(); i++)
    {
        vector<string> temp;
        temp.push_back(token[i]);
        temp.push_back(lexeme[i]);
        tokenLexeme.push_back(temp);
    }
}
*/
void setTokCounter(int num)
{
    tokCounter = num;
}

int getTokCounter()
{
    return tokCounter;
}

vector <string> getTok()
{
    return {token[tokCounter], lexeme[tokCounter]};
}

vector <string> getNextTok()
{
    tokCounter++;
    return getTok();
}

// function that prints the token and lexeme pairs used in the production rules, then removes them
// from the token and lexeme vectors
void vectorRemover()
{
    // print the token and lexeme pairs used in the production rules
    cout << "Token: " << token[tokCounter] << " Lexeme: " << lexeme[tokCounter] << endl;
    syntaxOutput << "Token: " << token[tokCounter] << " Lexeme: " << lexeme[tokCounter] << endl;

    // remove the token and lexeme pairs used in the production rules
    token.erase(token.begin() + tokCounter);
    lexeme.erase(lexeme.begin() + tokCounter);
}


// START OF RECURSIVE DESCENT PARSER
bool Aprime()
{
    // Augment the grammar
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
        if (getNextTok()[0] == "seperator" && getTok()[1] == "%%")
        {
            if (J())
            {
                if (N())
                {
                    if (getNextTok()[0] == "seperator" && getTok()[1] == "%%")
                    {
			            syntaxOutput << "<Rat19F>  ::=   <Opt Function Definitions>   %%  <Opt Declaration List>  <Statement List>  %%" << endl;
                        cout << "<Rat19F>  ::=   <Opt Function Definitions>   %%  <Opt Declaration List>  <Statement List>  %%" << endl;
                        return true;
                    }
                }
            }
        }
    }
    return false;
}

//
bool B()
{
    int tempTokCounter = getTokCounter();

    if (C())
    {
        syntaxOutput << "<Opt Function Definitions> ::= <Function Definitions> " << endl;
        cout << "<Opt Function Definitions> ::= <Function Definitions> " << endl;
        return true;
    }

    setTokCounter(tempTokCounter);
    syntaxOutput << "<Opt Function Definitions> ::= <Empty> " << endl;
    cout << "<Opt Function Definitions> ::= <Empty> " << endl;
    return true;
}

//
bool C()
{
    if (D())
    {
        int tempTokCounter = getTokCounter();

        if (C())
        {
            syntaxOutput << "<Function Definitions> ::= <Function> <Function Definitions>" << endl;
            cout << "<Function Definitions> ::= <Function> <Function Definitions>" << endl;
            return true;
        }
        else
        {
            setTokCounter(tempTokCounter);
            syntaxOutput << "<Function Definitions> ::= <Function>" << endl;
            cout << "<Function Definitions> ::= <Function>" << endl;
            return true;
        }
    }
    return false;
}

//
bool D()
{
    if (getNextTok()[0] == "keyword" && getTok()[1] == "function")
    {
        if (getNextTok()[0] == "identifier")
        {
            if (getNextTok()[0] == "seperator" && getTok()[1] == "(")
            {
                if (E())
                {
                    if (getNextTok()[0] == "seperator" && getTok()[1] == ")")
                    {
                        if (J())
                        {
                            if (I())
                            {
                                syntaxOutput << "<Function> ::= function  <Identifier> ( <Opt Parameter List> )  <Opt Declaration List>  <Body>" << endl;
                                cout << "<Function> ::= function  <Identifier> ( <Opt Parameter List> )  <Opt Declaration List>  <Body>" << endl;
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

//
bool E()
{
    int tempTokCounter = getTokCounter();

    if (F())
    {
        syntaxOutput << "<Opt Parameter List> ::= <Parameter List>" << endl;
        cout << "<Opt Parameter List> ::= <Parameter List>" << endl;
        return true;
    }

    setTokCounter(tempTokCounter);
    syntaxOutput << "<Opt Parameter List> ::= <Empty>" << endl;
    cout << "<Opt Parameter List> ::= <Empty>" << endl;
    return true;
}

//
bool F()
{
    if (G())
    {
        int tempTokCounter = getTokCounter();
        if (getNextTok()[0] == "seperator" && getTok()[1] == ",")
        {
            if (F())
            {
                syntaxOutput << "<Parameter List> ::= <Parameter> , <Parameter List>" << endl;
                cout << "<Parameter List> ::= <Parameter> , <Parameter List>" << endl;
                return true;
            }
        }
        else
        {
            setTokCounter(tempTokCounter);
            syntaxOutput << "<Parameter List> ::= <Parameter>" << endl;
            cout << "<Parameter List> ::= <Parameter>" << endl;
            return true;
        }
    }
    return false;
}

//
bool G()
{
    if (M())
    {
        if (H())
        {
            syntaxOutput << "<Parameter> ::= <IDs > <Qualifier>" << endl;
            cout << "<Parameter> ::= <IDs > <Qualifier>" << endl;
            return true;
        }
    }
    return false;
}

//
bool H()
{
    if (getNextTok()[0] == "keyword" && (getTok()[1] == "int" || getTok()[1] == "boolean" || getTok()[1] == "real"))
    {
        syntaxOutput << "<Qualifier> ::= " << getTok()[1] << endl;
        cout << "<Qualifier> ::= " << getTok()[1] << endl;
        return true;
    }
    return false; 
}

//
bool I()
{
    if (getNextTok()[0] == "seperator" && getTok()[1] == "{")
    {
        if (N())
        {
            if (getNextTok()[0] == "seperator" && getTok()[1] == "}")
            {
                syntaxOutput << "<Body> ::= { < Statement List> }" << endl;
                cout << "<Body> ::= { < Statement List> }" << endl;
                return true;
            }
        }
    }
    return false;
}

//
bool J()
{
    int tempTokCounter = getTokCounter();
    if (K())
    {
        syntaxOutput << "<Opt Declaration List> ::= <Declaration List>" << endl;
        cout << "<Opt Declaration List> ::= <Declaration List>" << endl;
        return true;
    }

    setTokCounter(tempTokCounter);
    syntaxOutput << "<Opt Declaration List> ::= <Empty>" << endl;
    cout << "<Opt Declaration List> ::= <Empty>" << endl;
    return true;
}

//
bool K()
{
    if (L())
    {
        if (getNextTok()[0] == "seperator" && getTok()[1] == ";")
        {
            int tempTokCounter = getTokCounter();
            if (K())
            {
                syntaxOutput << "<Declaration List> := <Declaration> ; <Declaration List>" << endl;
                cout << "<Declaration List> := <Declaration> ; <Declaration List>" << endl;
                return true;
            }
            else
            {
                setTokCounter(tempTokCounter);
                syntaxOutput << "<Declaration List> := <Declaration> ;" << endl;
                cout << "<Declaration List> := <Declaration> ;" << endl;
                return true;
            }
        }
    }
    return false;
}

//
bool L()
{
    if (H())
    {
        if (M())
        {
            syntaxOutput << "<Declaration> ::= <Qualifier > <IDs>" << endl;
            cout << "<Declaration> ::= <Qualifier > <IDs>" << endl;
            return true;
        }
    }
    return false;
}

//
bool M()
{
    if (getNextTok()[0] == "identifier")
    {
        int tempTokCounter = getTokCounter();
        if (getNextTok()[0] == "seperator" && getTok()[1] == "," && M())
        {
            syntaxOutput << "<IDs> ::= <Identifier> , <IDs>" << endl;
            cout << "<IDs> ::= <Identifier> , <IDs>" << endl;
            return true;
        }
        else
        {
            setTokCounter(tempTokCounter);
            syntaxOutput << "<IDs> ::= <Identifier>" << endl;
            cout << "<IDs> ::= <Identifier>" << endl;
            return true;
        }
    }
    return false;
}

//
bool N()
{
    if (O())
    {
        int tempTokCounter = getTokCounter();
        if (N())
        {
            syntaxOutput << "<Statement List> ::= <Statement> <Statement List>" << endl;
            cout << "<Statement List> ::= <Statement> <Statement List>" << endl;
            return true;
        }
        else
        {
            syntaxOutput << "<Statement List> ::= <Statement>" << endl;
            cout << "<Statement List> ::= <Statement>" << endl;
            return true;
            setTokCounter(tempTokCounter);
        }
        return true;
    }
    return false;
}

//
bool O()
{
    int tempTokCounter = getTokCounter();
    if (P())
    {
        syntaxOutput << "<Statement> ::= <Compound>" << endl;
        cout << "<Statement> ::= <Compound>" << endl;
        return true;
    }
    setTokCounter(tempTokCounter);
    if (Q())
    {
        syntaxOutput << "<Statement> ::= <Assign>" << endl;
        cout << "<Statement> ::= <Assign>" << endl;
        return true;
    }
    setTokCounter(tempTokCounter);
    if (R())
    {
        syntaxOutput << "<Statement> ::= <If>" << endl;
        cout << "<Statement> ::= <If>" << endl;
        return true;
    }
    setTokCounter(tempTokCounter);
    if (S())
    {
        syntaxOutput << "<Statement> ::= <Return>" << endl;
        cout << "<Statement> ::= <Return>" << endl;
        return true;
    }
    setTokCounter(tempTokCounter);
    if (T())
    {
        syntaxOutput << "<Statement> ::= <Print>" << endl;
        cout << "<Statement> ::= <Print>" << endl;
        return true;
    }
    setTokCounter(tempTokCounter);
    if (U())
    {
        syntaxOutput << "<Statement> ::= <Scan>" << endl;
        cout << "<Statement> ::= <Scan>" << endl;
        return true;
    }
    setTokCounter(tempTokCounter);
    if (V())
    {
        syntaxOutput << "<Statement> ::= <While>" << endl;
        cout << "<Statement> ::= <While>" << endl;
        return true;
    }
    return false;
}

//
bool P()
{
    if (getNextTok()[0] == "seperator" && getTok()[1] == "{")
    {
        if (N())
        {
            if (getNextTok()[0] == "seperator" && getTok()[1] == "}")
            {
                syntaxOutput << "<Compound> ::= { <Statement List> }" << endl;
                cout << "<Compound> ::= { <Statement List> }" << endl;
                return true;
            }
        }
    }
    return false;
}

//
bool Q()
{
    if (getNextTok()[0] == "identifier")
    {
        if (getNextTok()[0] == "operator" && getTok()[1] == "=")
        {
            if (Y())
            {
                if(getNextTok()[0] == "seperator" && getTok()[1] == ";")
                {
                    int tempTokCounter = getTokCounter();
                    syntaxOutput << "<Assign> ::= <Identifier> = <Expression> ;" << endl;
                    cout << "<Assign> ::= <Identifier> = <Expression> ;" << endl;
                    return true;
                }
            }
        }
    }
    return false;
}

//
bool R()
{
    int tempTokCounter = getTokCounter();
    if (getNextTok()[0] == "keyword" && getTok()[1] == "if")
    {
        if (getNextTok()[0] == "seperator" && getTok()[1] == "(")
        {
            if (W())
            {
                if (getNextTok()[0] == "seperator" && getTok()[1] == ")")
                {
                    if (O())
                    {
                        if (getNextTok()[0] == "keyword" && getTok()[1] == "fi")
                        {
                            syntaxOutput << "<If> ::= if ( <Condition> ) <Statement> fi" << endl;
                            cout << "<If> ::= if ( <Condition> ) <Statement> fi" << endl;
                            return true;
                        }
                    }
                }
            }
        }
    }
    setTokCounter(tempTokCounter);
    if (getNextTok()[0] == "keyword" && getTok()[1] == "if")
    {
        if (getNextTok()[0] == "seperator" && getTok()[1] == "(")
        {
            if (W())
            {
                if (getNextTok()[0] == "seperator" && getTok()[1] == ")")
                {
                    if (O())
                    {
                        if (getNextTok()[0] == "keyword" && getTok()[1] == "otherwise")
                        {
                            if (O())
                            {
                                if (getNextTok()[0] == "keyword" && getTok()[1] == "fi")
                                {
                                    syntaxOutput << "<If> ::= if ( <Condition> ) <Statement> otherwise <Statement> fi" << endl;
                                    cout << "<If> ::= if ( <Condition> ) <Statement> otherwise <Statement> fi" << endl;
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

//
bool S()
{
    if (getNextTok()[0] == "keyword" && getTok()[1] == "return")
    {
        int tempTokCounter = getTokCounter();
        if (Y())
        {
            if (getNextTok()[0] == "seperator" && getTok()[1] == ";")
            {
                syntaxOutput << "<Return> ::= return <Expression> ;" << endl;
                cout << "<Return> ::= return <Expression> ;" << endl;
                return true;
            }
        }
        setTokCounter(tempTokCounter);
        if (getNextTok()[0] == "seperator" && getTok()[1] == ";")
        {
            syntaxOutput << "<Return> ::= return ;" << endl;
            cout << "<Return> ::= return ;" << endl;
            return true;
        }
    }
    return false;
}

//
bool T()
{
    if (getNextTok()[0] == "keyword" && getTok()[1] == "put")
    {
        if (getNextTok()[0] == "seperator" && getTok()[1] == "(")
        {
            if (Y())
            {
                if (getNextTok()[0] == "seperator" && getTok()[1] == ")")
                {
                    if (getNextTok()[0] == "seperator" && getTok()[1] == ";")
                    {
                        syntaxOutput << "<Write> ::= put ( <Expression> );" << endl;
                        cout << "<Write> ::= put ( <Expression> );" << endl;
                        return true;
                    }
                }
            }
        }
    }
    return false;
}

//
bool U()
{
    if (getNextTok()[0] == "keyword" && getTok()[1] == "get")
    {
        if (getNextTok()[0] == "seperator" && getTok()[1] == "(")
        {
            if (M())
            {
                if (getNextTok()[0] == "seperator" && getTok()[1] == ")")
                {
                    if (getNextTok()[0] == "seperator" && getTok()[1] == ";")
                    {
                        syntaxOutput << "<Read> ::= get ( <IDs> );" << endl;
                        cout << "<Read> ::= get ( <IDs> );" << endl;
                    }
                return true;
                }
            }
        }
    }
    return false;
}

//
bool V()
{
    if (getNextTok()[0] == "keyword" && getTok()[1] == "while")
    {
        if (getNextTok()[0] == "seperator" && getTok()[1] == "(")
        {
            if (W())
            {
                if (getNextTok()[0] == "seperator" && getTok()[1] == ")")
                {
                    if (O())
                    {
                        syntaxOutput << "<While> ::= while ( <Condition> ) <Statement>" << endl;
                        cout << "<While> ::= while ( <Condition> ) <Statement>" << endl;
                        return true;
                    }
                }
            }
        }
    }
    return false;
}

//
bool W()
{
    if (Y())
    {
        if (X())
        {
            if (Y())
            {
                syntaxOutput << "<Condition> ::= <Expression> <Relop> <Expression>" << endl;
                cout << "<Condition> ::= <Expression> <Relop> <Expression>" << endl;
                return true;
            }
        }
    }
    return false;
}

//
bool X()
{
    if (getNextTok()[0] == "operator" && (getTok()[1] == "==" || getTok()[1] == "!=" || getTok()[1] == ">" || getTok()[1] == "<" || getTok()[1] == "=>" || getTok()[1] == "<="))
    {
        syntaxOutput << "<Relop> ::= " << getTok()[1] << endl;
        cout << "<Relop> ::= " << getTok()[1] << endl;
        return true;
    }
    return false;
}

//
bool Y()
{
    if (Z())
    {
        if (Yprime())
        {
            return true;
        }
    }
    return false;
}

//
bool Yprime()
{
    int tempTokCounter = getTokCounter();

    if (getNextTok()[0] == "operator" && getTok()[1] == "+")
    {
        if (Z())
        {
            if (Yprime())
            {
                syntaxOutput << "<Expression> ::= <Expression> + <Term>" << endl;
                cout << "<Expression> ::= <Expression> + <Term>" << endl;
                return true;
            }
        }
    }
    setTokCounter(tempTokCounter);
    if (getNextTok()[0] == "operator" && getTok()[1] == "-")
    {
        if (Z())
        {
            if (Yprime())
            {
                syntaxOutput << "<Expression> ::= <Expression> - <Term>" << endl;
                cout << "<Expression> ::= <Expression> - <Term>" << endl;
                return true;
            }
        }
    }
    setTokCounter(tempTokCounter);
    syntaxOutput << "<Expression> ::= <Empty>" << endl;
    cout << "<Expression> ::= <Empty>" << endl;
    return true;

}

//
bool Z()
{
    if (AA())
    {
        if (Zprime())
        {
            return true;
        }
    }
    return false;
}

//
bool Zprime()
{
    int tempTokCounter = getTokCounter();
    if (getNextTok()[0] == "operator" && getTok()[1] == "*")
    {
        if (AA())
        {
            if (Zprime())
            {
                syntaxOutput << "<Term> ::= <Term> * <Factor>" << endl;
                cout << "<Term> ::= <Term> * <Factor>" << endl;
                return true;
            }
        }
    }
    setTokCounter(tempTokCounter);
    if (getNextTok()[0] == "operator" && getTok()[1] == "/")
    {
        if (AA())
        {
            if (Zprime())
            {
                syntaxOutput << "<Term> ::= <Term> / <Factor>" << endl;
                cout << "<Term> ::= <Term> / <Factor>" << endl;
                return true;
            }
        }
    }
    setTokCounter(tempTokCounter);
    syntaxOutput << "<Term> ::= <Empty>" << endl;
    cout << "<Term> ::= <Empty>" << endl;
    return true;
}

//
bool AA()
{
    int tempTokCounter = getTokCounter();
    if (getNextTok()[0] == "operator" && getTok()[1] == "-")
    {
        if (BB())
        {
            syntaxOutput << "<Factor> ::= - <Primary>" << endl;
            cout << "<Factor> ::= - <Primary>" << endl;
            return true;
        }
    }
    setTokCounter(tempTokCounter);
    if (BB())
    {
        syntaxOutput << "<Factor> ::= <Primary>" << endl;
        cout << "<Factor> ::= <Primary>" << endl;
        return true;
    }
    return false;
}

//
bool BB()
{
    int tempTokCounter = getTokCounter();
    if (getNextTok()[0] == "identifier")
    {
        if (getNextTok()[0] == "seperator" && getTok()[1] == "(")
        {
            if (M())
            {
                if (getNextTok()[0] == "seperator" && getTok()[1] == ")")
                {
                    syntaxOutput << "<Primary> ::= <Identifier> ( <IDs> )" << endl;
                    cout << "<Primary> ::= <Identifier> ( <IDs> )" << endl;
                    return true;
                }
            }
        }
    }
    setTokCounter(tempTokCounter);
    if (getNextTok()[0] == "identifier")
    {
        syntaxOutput << "<Primary> ::= <Identifier>" << endl;
        cout << "<Primary> ::= <Identifier>" << endl;
        return true;
    }
    setTokCounter(tempTokCounter);
    if (getNextTok()[0] == "integer")
    {
        syntaxOutput << "<Primary> ::= <Integer>" << endl;
        cout << "<Primary> ::= <Integer>" << endl;
        return true;
    }
    setTokCounter(tempTokCounter);
    if (getNextTok()[0] == "seperator" && getTok()[1] == "(")
    {
        if (Y())
        {
            if (getNextTok()[0] == "seperator" && getTok()[1] == ")")
            {
                syntaxOutput << "<Primary> ::= ( <Expression> )" << endl;
                cout << "<Primary> ::= ( <Expression> )" << endl;
                return true;
            }
        }
    }
    setTokCounter(tempTokCounter);
    if (getNextTok()[0] == "real")
    {
        syntaxOutput << "<Primary> ::= <Real>" << endl;
        cout << "<Primary> ::= <Real>" << endl;
        return true;
    }
    setTokCounter(tempTokCounter);
    if (getNextTok()[0] == "keyword" && getTok()[1] == "true")
    {
        syntaxOutput << "<Primary> ::= true" << endl;
        cout << "<Primary> ::= true" << endl;
        return true;
    }
    return false;
}

void syntaxAnalyzer()
{
    while (getNextTok()[0] != "EOF")
    {
        if (Aprime())
        {
            cout << "Syntax is correct" << endl;
        }
        else
        {
            cout << "Syntax is incorrect" << endl;
        }
    }
}

#endif