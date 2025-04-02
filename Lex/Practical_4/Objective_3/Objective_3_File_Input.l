%{
#include <stdio.h>
int char_count = 0, word_count = 0, line_count = 0;
%}

%%
[^ \t\n]+  { word_count++; char_count += yyleng; }
[ \t]      { char_count += yyleng; }
\n         { line_count++; char_count++; }
.          { char_count++; }
%%

int main() {
    FILE *file = fopen("input.txt", "r");
    if (!file) {
        printf("Error opening file!\n");
        return 1;
    }
    yyin = file;
    yylex();
    fclose(file);
    
    printf("Characters: %d\n", char_count);
    printf("Words: %d\n", word_count);
    printf("Lines: %d\n", line_count);
    return 0;
}

int yywrap() {
    return 1;
}
