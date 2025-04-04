#include<stdio.h>
#include<ctype.h>
#include<string.h>

/**********************************************************************************************/
/* 
 * CS 382 Lexical Analyzer - Project Documentation
 * 
 * Grammar (BNF Form) for Lexical Analysis:
 * <letter>         ::= a | b | ... | z | A | B | ... | Z
 * <digit>          ::= 0 | 1 | ... | 9
 * <identifier>     ::= <letter> {<letter> | <digit>}
 * <int_literal>    ::= <digit> {<digit>}
 * <add_op>         ::= + | -
 * <mult_op>        ::= * | /
 * <assign_op>      ::= =
 * <lparen>         ::= (
 * <rparen>         ::= )
 * <token>          ::= <identifier> | <int_literal> | <add_op> | <mult_op> | <assign_op> | <lparen> | <rparen>
 *
 * This is BNF (Backus-Naur Form) since it uses recursive reasoning.
 */
/**********************************************************************************************/

/* Global declarations for variables and functions */

// Variables (Documenting data structures and roles per rubric)
int charClass;            // Character class of nextChar: LETTER, DIGIT, or UNKNOWN
char lexeme[100];         // Stores the current lexeme
char nextChar;            // Holds the next character read from input
int lexLen;               // Current length of lexeme
int token;                // Placeholder (unused here)
int nextToken;            // Token type of current lexeme
FILE *in_fp, *out_fp, *fopen(); // File pointers

// Functions 
void addChar();           // Adds nextChar to lexeme
void getChar();           // Gets the next char and classifies it
void getNonBlank();       // Skips whitespace
int lex();                // Lexical analyzer function

// Classes (following naming conventions for constants)
#define LETTER 0
#define DIGIT 1
#define UNKNOWN 99

// Token Codes (following all-caps convention per C standard and rubric)
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
    if ((in_fp = fopen("input2.txt", "r")) == NULL) {
        printf("ERROR - cannot open input file \n");
        return 1;
    }

    /* Open output file */
    if ((out_fp = fopen("output2.txt", "w")) == NULL) {
        printf("ERROR - cannot create output file \n");
        fclose(in_fp);
        return 1;
    }

    getChar(); // Get the first character

    // Main lexical analyzer loop
    do {
        lex(); // Call the lex function
    } while (nextToken != EOF); // Continue until EOF is reached

    /* Close files */
    fclose(in_fp);
    fclose(out_fp);

    printf("Lexical analysis results written to output.txt\n");

    return 0;
}

/**********************************************************************************************/
/* 
 * Function: lookup(char ch)
 * Purpose: Lookup operators and parentheses.
 * Grammar Rule Applied: <add_op> | <mult_op> | <assign_op> | <lparen> | <rparen>
 */

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
/*
 * Function: addChar()
 * Purpose: Add the current character to lexeme
 * Grammar Usage: Supports building <identifier> and <int_literal>
 */

void addChar() {
    if (lexLen <= 98) {
        lexeme[lexLen++] = nextChar;
        lexeme[lexLen] = 0;
    } else {
        printf("Error - lexeme is too long \n");
    }
}

/**********************************************************************************************/
/*
 * Function: getChar()
 * Purpose: Read next character and determine its class
 * Grammar Mapping: Determines if it could start a <letter>, <digit>, or <unknown>
 */

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
/*
 * Function: getNonBlank()
 * Purpose: Skip whitespace
 * Grammar Relevance: Not tied to a specific rule, but ensures tokens are properly delimited
 */

void getNonBlank() {
    while (isspace(nextChar)) {
        while (isspace(nextChar)) {
            getChar();
        }
    }
}

/**********************************************************************************************/
/*
 * Function: lex()
 * Purpose: The core lexical analyzer
 * Grammar Mapping:
 *   - <identifier> ::= <letter> {<letter> | <digit>}
 *   - <int_literal> ::= <digit> {<digit>}
 *   - <token> ::= operators/parentheses/etc.
 */

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
    fprintf(out_fp, "Next token is: %d, Next lexeme is %s\n", nextToken, lexeme);

    return nextToken;
}   /* End of lex */