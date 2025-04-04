#include<stdio.h>
#include<ctype.h>
#include<string.h>
#include "../lexicalAnalyzer.h"

/* Global declarations for variables and functions */

// Variables
int charClass;
char lexeme[100];
char nextChar;
int lexLen;
int token;
int nextToken;
FILE *in_fp, *out_fp, *fopen();

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
int main() {
    /* Open input file */
    if ((in_fp = fopen("input.txt", "r")) == NULL) {
        printf("ERROR - cannot open input file \n");
        return 1;
    }

    /* Open output file */
    if ((out_fp = fopen("output.txt", "w")) == NULL) {
        printf("ERROR - cannot create output file \n");
        fclose(in_fp);
        return 1;
    }

    if ((out_fp = fopen("Parser/tokens.txt", "w")) == NULL) { // In main()
        printf("ERROR - cannot create tokens.txt \n");
        fclose(in_fp);
        return 1;
    }

    getChar(); // Get the first character

    do {
        lex(); // Call the lex function
    } while (nextToken != EOF); // Continue until EOF is reached

    /* Close files */
    fclose(in_fp);
    fclose(out_fp);

    printf("Results written to output.txt\n");

    return 0;
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

/**********************************************************************************************/

/* addChar() - a function to add nextChar to lexeme */
void addChar() {
    if (lexLen <= 98) {
        lexeme[lexLen++] = nextChar;
        lexeme[lexLen] = 0;
    } else {
        printf("Error - lexeme is too long \n");
    }
}

/**********************************************************************************************/
/* getChar - a function to get the next character of input and determine its character class */

void getChar() {
    if ((nextChar = getc(in_fp)) != EOF) {
        if (isalpha(nextChar)) {
            charClass = LETTER;
        } else if (isdigit(nextChar)) {
            charClass = DIGIT;
        } else {
            charClass = UNKNOWN;
        }
    } else {
        charClass = EOF;
    }
}

/**********************************************************************************************/

/* getNonBlank - a function to call getChar until it returns a non-whitespace character */

void getNonBlank() {
    while (isspace(nextChar)) {
        while (isspace(nextChar)) {
            getChar();
        }
    }
}

/**********************************************************************************************/
/* lex - a simple lexical analyzer for arithmetic expressions */

int lex() {
    lexLen = 0;
    getNonBlank();
    switch (charClass) {
        /* Parse Identifiers */
        case LETTER:
            addChar();
            getChar();
            while (charClass == LETTER || charClass == DIGIT) {
                addChar();
                getChar();
            }
            nextToken = IDENT;
            break;

        /* Parse integer literals */
        case DIGIT:
            addChar();
            getChar();
            while (charClass == DIGIT) {
                addChar();
                getChar();
            }
            nextToken = INT_LIT;
            break;

        /* Parentheses and operators */
        case UNKNOWN:
            lookup(nextChar);
            getChar();
            break;
        
        /* EOF */
        case EOF:
            nextToken = EOF;
            lexeme[0] = 'E';
            lexeme[1] = 'O';
            lexeme[2] = 'F';
            lexeme[3] = 0;
            break;
    }   /* End of switch */

    /* Write the result to the output file */
    //fprintf(out_fp, "Next token is: %d, Next lexeme is %s\n", nextToken, lexeme);
    fprintf(out_fp, "%d %s\n", nextToken, lexeme); // In lex()

    return nextToken;
}   /* End of lex */