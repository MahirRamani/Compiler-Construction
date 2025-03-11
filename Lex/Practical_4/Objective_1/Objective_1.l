%{
#include <stdio.h>
%}

%%
[0-9]+  { printf("%s\n", yytext); }
.        { /* Ignore other characters */ }
\n       { return 0; } 
%%

int main() {
    printf("Enter a string: ");
    yylex();
    return 0;
}

int yywrap() {
    return 1;
}
