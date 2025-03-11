%{
#include <stdio.h>
%}

%%
charusat  { printf("university"); }
CHARUSAT  { printf("UNIVERSITY"); }
[Cc]harusat  { printf("University"); }
.        { printf("%s", yytext); }
\n       { printf("\n"); return 0; } 
%%

int main() {
    printf("Enter a string: ");
    yylex();
    return 0;
}

int yywrap() {
    return 1;
}
