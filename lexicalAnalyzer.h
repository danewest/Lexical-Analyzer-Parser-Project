#ifndef LEXICAL_ANALYZER_H
#define LEXICAL_ANALYZER_H

#include <stdio.h>

// Function Prototypes
int lex();
void getChar();
void addChar();
int lookup(char ch);

// Global Variables declared as extern
extern int nextToken;
extern char lexeme[100];
extern FILE *in_fp; // Declare in_fp as extern
extern FILE *out_fp; // Declare out_fp as extern

#endif