// main program for the a2 syntax analyzer

#include "lexer.h"
#include "syntax.h"

#include <iostream>
#include <string>
#include <fstream>
#include <string>

int main ()
{
    // Lexer portion
    // Read file and tokenize to output text file
    openFiles();    // Ask the user for the file names and open the files
    //initPrint();    // Print the header
    lexer();    // Run the lexer
    endPrint(); // Print the footer

    // Syntax analyzer portion
    tester();   // test the token and lexeme vectors
    return 0;

}