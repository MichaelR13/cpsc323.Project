// Build of a lexer
// The lexer will be built entirely using a finite state machine

// MUST write the Regular Expressions for Identifiers, Real, and Integer
// Also show NFSM using Thompson's construction

/* Program must read a file containing the source code of the language to generate tokens and write out the 
   results to an output file. 
*/
// Print both, the tokens and lexemes

/* Psuedo code below:
     while not finished (i.e. not end of the source file) do
          call the lexer for a token
          print the token and lexeme
     endwhile
*/

/* Sample test case:

INPUT: while  (fahr <= upper)   a = 23.00; endwhile  [* this is sample *]

OUTPUT: 

token           lexeme
-----           ------
keyword         while
separator       (
identifier      fahr
operator        <=
identifier      upper
separator       )
identifier      a
operator        =
real            23.00
separator       ;
keyword         endwhile
*/

#pragma once

#include "lexer.hpp"

#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <cctype>

using namespace std;


int main()
{
     // Open the source code file

     // while not finished (i.e. not end of the source file) do
     //     call the lexer for a token
     //     receive the token and lexeme from vectors in lexer
     //     open the output file (output.txt)
     //     print the token and lexeme to the output file
     //     close the output file
     
     // end while

     // Close the source code file

     return 0;
}
