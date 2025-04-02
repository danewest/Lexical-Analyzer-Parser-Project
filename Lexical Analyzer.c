#include<stdio.h>
#include<ctype.h>
#include<string.h>

/* Global declarations for variables and functions */

// Variables
int charClass;
char lexeme[100];
char nextChar;
int lexLen;
int token;
int nextToken;
FILE *in_fp, *fopen();

// Functions
void addChar();
void getChar();
void getNonBlank();
int lex();

// Classes
#define LETTER 0
#define DIGIT 1
#define UNKNOWN 99

// Token Codes
#define INT_LIT 10
#define IDENT 11
#define ASSIGN_OP 20
#define ADD_OP 21
#define SUB_OP 22
#define MULT_OP 23
#define DIV_OP 24
#define LEFT_PAREN 25
#define RIGHT_PAREN 26

/**********************************************************************************************/
/* main driver */
main() {
    /* Open the input data file and process its contents */
    if ((in_fp))
}