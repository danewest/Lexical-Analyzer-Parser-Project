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
    if ((in_fp = fopen("input.txt", "r")) == NULL) {
        printf("ERROR - cannot open input file \n");
    } else {
        getChar(); // Get the first character
        do {
            lex(); // Call the lex function
        } while (nextToken != EOF); // Continue until EOF is reached
    }
}

/**********************************************************************************************/
/* lookup - function to lookup operators and parentheses and return the token*/

int lookup(char ch) {
    switch (ch) {
        case '(':
            addChar();
            nextToken = LEFT_PAREN;
            break;
        case ')':
            addChar();
            nextToken = RIGHT_PAREN;
            break;
        case '+':
            addChar();
            nextToken = ADD_OP;
            break;
        case '-':
            addChar();
            nextToken = SUB_OP;
            break;
        case '*':
            addChar();
            nextToken = MULT_OP;
            break;
        case '/':
            addChar();
            nextToken = DIV_OP;
            break;
        case '=':
            addChar();
            nextToken = ASSIGN_OP;
            break;
        default:
            addChar();
            nextToken = EOF;
            break;
    }
    return nextToken;
}