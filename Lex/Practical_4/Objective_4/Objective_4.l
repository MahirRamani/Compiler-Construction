%{
#include <stdio.h>
#include <string.h>
#include <ctype.h>

int has_lower = 0, has_upper = 0, has_digit = 0, has_special = 0;
char password[16]; // Store input (max 15 + 1 for '\0')
int len = 0;
%}

%%
[a-z]   { has_lower = 1; if (len < 15) password[len++] = yytext[0]; }
[A-Z]   { has_upper = 1; if (len < 15) password[len++] = yytext[0]; }
[0-9]   { has_digit = 1; if (len < 15) password[len++] = yytext[0]; }
[*;#$@] { has_special = 1; if (len < 15) password[len++] = yytext[0]; }

\n      { password[len] = '\0'; return 1; }  // Terminate input on Enter key
.       { if (len < 15) password[len++] = yytext[0]; } // Store other characters
%%

int main() {
    printf("Enter password: ");
    yylex(); // Read input until Enter is pressed

    if (len >= 9 && len <= 15 && has_lower && has_upper && has_digit && has_special) {
        printf("Valid password\n");
    } else {
        printf("Invalid password\n");
    }

    return 0;
}

int yywrap() {
    return 1;
}
