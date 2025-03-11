%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Function to print token type
void print_token(const char *type, const char *text) {
    printf("%s: %s\n", type, text);
}
%}

DIGIT   [0-9]
LETTER  [a-zA-Z]
SPECIAL [*;#$@]
WHITESPACE [ \t\r]+
COMMENT_SINGLE "//".*
COMMENT_MULTI "/*"([^*]|\*+[^*/])*\*+"/"

KEYWORD "int"|"char"|"return"|"main"

OPERATOR "="|"+"|"-"|"*"|"/"|"=="|"!="|"<="|">="|"<"|">"

PUNCTUATION "["|"]"|"("|")"|"{"|"}"|","|";"

IDENTIFIER {LETTER}({LETTER}|{DIGIT})*

CONSTANT {DIGIT}+
CHARACTER_CONST "'"[^']"'"

%%
{WHITESPACE}     { /* Ignore whitespace */ }

{COMMENT_SINGLE} { printf("Comment: %s\n", yytext); }
{COMMENT_MULTI}  { printf("Comment: Block Comment\n"); }

{KEYWORD}        { print_token("Keyword", yytext); }
{IDENTIFIER}     { print_token("Identifier", yytext); }
{CONSTANT}       { print_token("Constant", yytext); }
{CHARACTER_CONST} { print_token("String", yytext); }
{PUNCTUATION}    { print_token("Punctuation", yytext); }
{OPERATOR}       { print_token("Operator", yytext); }

{DIGIT}+{LETTER}+ { printf("Lexical Error: %s\n", yytext); }

.                { printf("Lexical Error: %s\n", yytext); }

%%

int main(int argc, char **argv) {
    if (argc < 2) {
        printf("Usage: %s <filename>\n", argv[0]);
        return 1;
    }

    FILE *file = fopen(argv[1], "r");
    if (!file) {
        printf("Error: Could not open file %s\n", argv[1]);
        return 1;
    }

    yyin = file;
    printf("Processing file: %s\n", argv[1]);
    yylex();
    
    fclose(file);
    return 0;
}

int yywrap() {
    return 1;
}
