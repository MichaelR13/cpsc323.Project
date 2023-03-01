// This will be the lexer class, which will be used to tokenize the input
// 6 token types: keywords, identifiers, operators, separators, integers, and reals
// It will primarily token definitions, as well as the lexer class

#pragma once

#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <cctype>

using namespace std;

// Make 2 finite state machines, one for the Identifier and one for Integer + Real

// Finite State Machine for Identifiers

// Start lexer function

void lexer(char* str)
{
     // Objective: Tokenize the input string, store the lexemes and token types in vectors, 
     // pass those vectors to main
}