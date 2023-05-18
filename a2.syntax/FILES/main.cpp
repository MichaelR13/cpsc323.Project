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
    // lexical analyzer
    lexicalAnalyzer();
    // syntax analyzer
    syntaxAnalyzer();

    return 0;

}