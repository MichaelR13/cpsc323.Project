// main program for the a2 syntax analyzer

#include <iostream>
#include <string>
#include <fstream>
#include <string>

#include "lexer.h"
#include "syntaxAnalyzer.h"

using namespace std;


int main ()
{
    openFiles();
    lexer();
    parseTokens();
    /*
    openFiles();    // Ask the user for the file names and open the files
    openSyntaxFile(); // open syntax file
    lexer();    // Run the lexer
    parseTokens();  // Parse the tokens

    closeSyntaxFile(); // close syntax file
    */
    return 0;

}