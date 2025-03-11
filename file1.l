%option noyywrap
%{
    #include<stdio.h>
    int v=0, c=0; // Vowel and consonant counters
    #define yywrap() 1
%}

%%

[aeiouAEIOU] { v++; } // Count vowels
[a-zA-Z]     { c++; } // Count all letters (will adjust consonants later)
[ \t\n]      ;        // Ignore spaces, tabs, and newlines
.            ;        // Ignore all other characters

%%

 // Prevent errors related to file reading

int main(){
    printf("Enter a string: ");
    yylex();
    c -= v;
    // Adjust consonant count: Total letters - vowels
    

    printf("\nVowels: %d", v);
    printf("\nConsonants: %d", c);
    return 0;
}
