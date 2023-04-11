// Implementation of all recursive functions for parser

// First remove left recursion from the grammar
// Then Use a Recursive Descent Parser (RDP) to parse the input
// NOTE: Generate error messages for syntax errors

// If the rule the function represents is test true (this rule is used), then print the rule
// 36 non-deterministic symbols, so 36 functions will be written

/* Sample output:
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

*/

#include "syntax.h"

// Function prototypes
bool R1();
bool R2();
bool R3();
bool R4();
bool R5();
bool R6();
bool R7();
bool R8();
bool R9();
bool R10();
bool R11();
bool R12();
bool R13();
bool R14();
bool R15();
bool R16();
bool R17();
bool R18();
bool R19();
bool R20();
bool R21();
bool R22();
bool R23();
bool R24();
bool R25();
bool R26();
bool R27();
bool R28();
bool R29();
bool R30();
bool R31();
bool R32();
bool R33();
bool R34();
bool R35();
bool R36();

// Function definitions