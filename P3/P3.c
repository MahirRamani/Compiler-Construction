// #include <stdio.h>
// #include <stdlib.h>
// #include <string.h>
// #include <ctype.h>

// // Define keywords
// const char *keywords[] = {"int", "char", "return", "if", "else", "while", "for", "float", "double", "void"};
// const int num_keywords = 10;

// // Symbol table for identifiers
// char symbol_table[100][50];
// int symbol_table_index = 0;

// // Function to check if a string is a keyword
// int is_keyword(const char *str)
// {
//     for (int i = 0; i < num_keywords; i++)
//     {
//         if (strcmp(str, keywords[i]) == 0)
//         {
//             return 1;
//         }
//     }
//     return 0;
// }

// // Function to check if a character is a punctuation
// int is_punctuation(char ch)
// {
//     return strchr("(){};,", ch) != NULL;
// }

// // Function to check if a character is an operator
// int is_operator(char ch)
// {
//     return strchr("=+-*/<>!", ch) != NULL;
// }

// // Function to add an identifier to the symbol table
// void add_to_symbol_table(const char *identifier)
// {
//     for (int i = 0; i < symbol_table_index; i++)
//     {
//         if (strcmp(symbol_table[i], identifier) == 0)
//         {
//             return; // Identifier already exists
//         }
//     }
//     strcpy(symbol_table[symbol_table_index++], identifier);
// }

// // Function to check if a token is valid
// // int is_valid_token(const char *token)
// // {
// //     if (isdigit(token[0]))
// //     {
// //         for (int i = 1; token[i] != '\0'; i++)
// //         {
// //             if (!isdigit(token[i]))
// //             {
// //                 return 0; // Invalid if digits are followed by non-digits
// //             }
// //         }
// //         return 1;
// //     }
// //     return 1; // Assume valid for non-numeric tokens; additional checks can be added
// // }

// // Function to check if a token is a valid number (float or integer)
// int is_valid_number(const char *token) {
//     int dot_count = 0;
//     for (int i = 0; token[i] != '\0'; i++) {
//         if (token[i] == '.') {
//             dot_count++;
//         } else if (!isdigit(token[i])) {
//             return 0; // Invalid character in the number
//         }
//     }
//     return dot_count <= 1; // A valid number can have at most one dot
// }

// // Function to check if a token is valid (constant validation)
// int is_valid_token(const char *token) {
//     if (isdigit(token[0]) || (token[0] == '.' && isdigit(token[1]))) {
//         return is_valid_number(token); // Check if it's a valid number (float or integer)
//     }
//     return 1; // Assume valid for non-numeric tokens; additional checks can be added
// }

// int is_shorthand_operator(const char *str) {
//     const char *shorthand_ops[] = {"+=", "-=", "*=", "/=", "%=", "++", "--", "&&", "||"};
//     int num_shorthand_ops = sizeof(shorthand_ops) / sizeof(shorthand_ops[0]);
//     for (int i = 0; i < num_shorthand_ops; i++) {
//         if (strcmp(str, shorthand_ops[i]) == 0) {
//             return 1;
//         }
//     }
//     return 0;
// }

// // Lexical analyzer function
// void lexical_analyzer(const char *filename)
// {
//     FILE *file = fopen(filename, "r");
//     if (!file)
//     {
//         printf("Error: Could not open file %s\n", filename);
//         return;
//     }

//     char ch, buffer[50];
//     int index = 0;
//     int in_comment = 0;

//     printf("TOKENS\n");
//     while ((ch = fgetc(file)) != EOF)
//     {
//         // Handle comments
//         if (in_comment)
//         {
//             if (ch == '*' && (ch = fgetc(file)) == '/')
//             {
//                 in_comment = 0; // End of multi-line comment
//             }
//             else if (ch == EOF)
//             {
//                 break; // Ensure EOF ends comment processing
//             }
//             continue;
//         }
//         if (ch == '/')
//         {
//             char next_char = fgetc(file); // Peek at the next character
//             if (next_char == '/')
//             {
//                 // Single-line comment
//                 while ((ch = fgetc(file)) != '\n' && ch != EOF)
//                     ; // Skip till end of line
//                 continue;
//             }
//             else if (next_char == '*')
//             {
//                 // Multi-line comment
//                 in_comment = 1;
//                 continue;
//             }
//             else
//             {
//                 // Not a comment, put the character back
//                 ungetc(next_char, file);
//             }
//         }

//         // Handle white spaces
//         if (isspace(ch))
//         {
//             if (index > 0)
//             {
//                 buffer[index] = '\0';
//                 if (is_keyword(buffer))
//                 {
//                     printf("Keyword: %s\n", buffer);
//                 }
//                 else if (isdigit(buffer[0]) && !is_valid_token(buffer))
//                 {
//                     printf("Lexical Error: Invalid lexeme %s\n", buffer);
//                 }
//                 else if (isdigit(buffer[0]))
//                 {
//                     printf("Constant: %s\n", buffer);
//                 }
//                 else if (isalpha(buffer[0]))
//                 {
//                     printf("Identifier: %s\n", buffer);
//                     add_to_symbol_table(buffer);
//                 }
//                 else
//                 {
//                     printf("Lexical Error: Invalid lexeme %s\n", buffer);
//                 }
//                 index = 0;
//             }
//             continue;
//         }

//         // Handle strings (double-quoted)
//         if (ch == '"') {
//             buffer[index++] = ch; // Add the starting quote
//             while ((ch = fgetc(file)) != '"' && ch != EOF) {
//                 buffer[index++] = ch; // Add content inside the string
//             }
//             if (ch == '"') {
//                 buffer[index++] = ch; // Add the closing quote
//                 buffer[index] = '\0'; // Null-terminate the string
//                 printf("String: %s\n", buffer);
//                 index = 0;
//             } else {
//                 printf("Lexical Error: Unclosed string literal\n");
//                 index = 0;
//             }
//             continue;
//         }

//         // Handle punctuation
//         if (is_punctuation(ch))
//         {
//             if (index > 0)
//             {
//                 buffer[index] = '\0';
//                 if (is_keyword(buffer))
//                 {
//                     printf("Keyword: %s\n", buffer);
//                 }
//                 else if (isdigit(buffer[0]) && !is_valid_token(buffer))
//                 {
//                     printf("Lexical Error: Invalid lexeme %s\n", buffer);
//                 }
//                 else if (isdigit(buffer[0]))
//                 {
//                     printf("Constant: %s\n", buffer);
//                 }
//                 else if (isalpha(buffer[0]))
//                 {
//                     printf("Identifier: %s\n", buffer);
//                     add_to_symbol_table(buffer);
//                 }
//                 else
//                 {
//                     printf("Lexical Error: Invalid lexeme %s\n", buffer);
//                 }
//                 index = 0;
//             }
//             printf("Punctuation: %c\n", ch);
//             continue;
//         }

//         // Handle operators (including shorthand operators)
//         if (is_operator(ch)) {
//             buffer[index++] = ch; // Start the operator buffer
//             ch = fgetc(file); // Look at the next character

//             // Check for shorthand operators like ++, +=, etc.
//             if (ch == '+' || ch == '-' || ch == '=' || ch == '/' || ch == '*' || ch == '&' || ch == '|') {
//                 buffer[index++] = ch;
//                 char next_char = fgetc(file);
//                 buffer[index++] = next_char;
//                 buffer[index] = '\0'; // Null-terminate the operator string

//                 // Check if it's a shorthand operator
//                 if (is_shorthand_operator(buffer)) {
//                     printf("Operator: %s\n", buffer);
//                 } else {
//                     printf("Lexical Error: Invalid operator %s\n", buffer);
//                 }
//                 index = 0;
//                 continue;
//             } else {
//                 ungetc(ch, file); // Put back the character if not part of shorthand operator
//             }
//             // Handle individual operators like +, -, etc.
//             buffer[index] = '\0';
//             printf("Operator: %s\n", buffer);
//             index = 0;
//             continue;
//         }

//         // Handle character constants
//         if (ch == '\'')
//         {
//             buffer[index++] = ch;
//             ch = fgetc(file);
//             if (isalnum(ch) || ispunct(ch))
//             {
//                 buffer[index++] = ch;
//                 ch = fgetc(file);
//                 if (ch == '\'')
//                 {
//                     buffer[index++] = ch;
//                     buffer[index] = '\0';
//                     printf("Constant: %s\n", buffer);
//                     index = 0;
//                 }
//                 else
//                 {
//                     printf("Lexical Error: Invalid character constant\n");
//                     index = 0;
//                 }
//             }
//             else
//             {
//                 printf("Lexical Error: Invalid character constant\n");
//                 index = 0;
//             }
//             continue;
//         }

//         // Add character to buffer
//         buffer[index++] = ch;
//     }

//     // Handle the last token
//     if (index > 0)
//     {
//         buffer[index] = '\0';
//         if (is_keyword(buffer))
//         {
//             printf("Keyword: %s\n", buffer);
//         }
//         else if (isdigit(buffer[0]) && !is_valid_token(buffer))
//         {
//             printf("Lexical Error: Invalid lexeme %s\n", buffer);
//         }
//         else if (isdigit(buffer[0]))
//         {
//             printf("Constant: %s\n", buffer);
//         }
//         else if (isalpha(buffer[0]))
//         {
//             printf("Identifier: %s\n", buffer);
//             add_to_symbol_table(buffer);
//         }
//         else
//         {
//             printf("Lexical Error: Invalid lexeme %s\n", buffer);
//         }
//     }

//     fclose(file);

//     // Print the symbol table
//     printf("\nSYMBOL TABLE ENTRIES\n");
//     for (int i = 0; i < symbol_table_index; i++)
//     {
//         printf("%d) %s\n", i + 1, symbol_table[i]);
//     }
// }

// int main()
// {
//     const char *filename = "T1.c";
//     lexical_analyzer(filename);
//     return 0;
// }

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Define keywords
const char *keywords[] = {"int", "char", "return", "if", "else", "while", "for", "float", "double", "void"};
const int num_keywords = 10;

// Symbol table for identifiers
char symbol_table[100][50];
int symbol_table_index = 0;

// Function to check if a string is a keyword
int is_keyword(const char *str)
{
    for (int i = 0; i < num_keywords; i++)
    {
        if (strcmp(str, keywords[i]) == 0)
        {
            return 1;
        }
    }
    return 0;
}

// Function to check if a character is a punctuation
int is_punctuation(char ch)
{
    return strchr("(){};,", ch) != NULL;
}

// Function to check if a character is an operator
int is_operator(char ch)
{
    return strchr("=+-*/<>!&|^", ch) != NULL;
}

// Function to check if a string is a valid shorthand operator
int is_shorthand_operator(const char *str)
{
    const char *shorthand_ops[] = {"+=", "-=", "*=", "/=", "%=", "++", "--", "&&", "||"};
    int num_shorthand_ops = sizeof(shorthand_ops) / sizeof(shorthand_ops[0]);
    for (int i = 0; i < num_shorthand_ops; i++)
    {
        if (strcmp(str, shorthand_ops[i]) == 0)
        {
            return 1;
        }
    }
    return 0;
}

// Function to add an identifier to the symbol table
void add_to_symbol_table(const char *identifier)
{
    for (int i = 0; i < symbol_table_index; i++)
    {
        if (strcmp(symbol_table[i], identifier) == 0)
        {
            return; // Identifier already exists
        }
    }
    strcpy(symbol_table[symbol_table_index++], identifier);
}

// Function to check if a string is a valid number (float or integer)
int is_valid_number(const char *token)
{
    int dot_count = 0;
    int start = 0;

    if (token[0] == '.')
    {
        start = 1; // Allow numbers starting with a dot like .20
    }

    for (int i = start; token[i] != '\0'; i++)
    {
        if (token[i] == '.')
        {
            dot_count++;
        }
        else if (!isdigit(token[i]))
        {
            return 0; // Invalid character in the number
        }
    }

    return dot_count <= 1; // A valid number can have at most one dot
}

// Function to check if a string is a valid token (constant validation)
int is_valid_token(const char *token)
{
    if (isdigit(token[0]) || (token[0] == '.' && isdigit(token[1])))
    {
        return is_valid_number(token); // Check if it's a valid number (float or integer)
    }
    return 1; // Assume valid for non-numeric tokens; additional checks can be added
}

// Lexical analyzer function
void lexical_analyzer(const char *filename)
{
    FILE *file = fopen(filename, "r");
    if (!file)
    {
        printf("Error: Could not open file %s\n", filename);
        return;
    }

    char ch, buffer[50];
    int index = 0;
    int in_comment = 0;

    printf("TOKENS\n");
    while ((ch = fgetc(file)) != EOF)
    {
        // Handle comments
        if (in_comment)
        {
            if (ch == '*' && (ch = fgetc(file)) == '/')
            {
                in_comment = 0; // End of multi-line comment
            }
            else if (ch == EOF)
            {
                break; // Ensure EOF ends comment processing
            }
            continue;
        }
        if (ch == '/')
        {
            char next_char = fgetc(file); // Peek at the next character
            if (next_char == '/')
            {
                // Single-line comment
                while ((ch = fgetc(file)) != '\n' && ch != EOF)
                    ; // Skip till end of line
                continue;
            }
            else if (next_char == '*')
            {
                // Multi-line comment
                in_comment = 1;
                continue;
            }
            else
            {
                // Not a comment, put the character back
                ungetc(next_char, file);
            }
        }

        // Handle white spaces (skip)
        if (isspace(ch))
        {
            if (index > 0)
            {
                buffer[index] = '\0';
                if (is_keyword(buffer))
                {
                    printf("Keyword: %s\n", buffer);
                }
                else if (isdigit(buffer[0]) && !is_valid_token(buffer))
                {
                    printf("Lexical Error: Invalid lexeme %s\n", buffer);
                }
                else if (isdigit(buffer[0]))
                {
                    printf("Constant: %s\n", buffer);
                }
                else if (isalpha(buffer[0]))
                {
                    printf("Identifier: %s\n", buffer);
                    add_to_symbol_table(buffer);
                }
                else
                {
                    printf("Lexical Error: Invalid lexeme %s\n", buffer);
                }
                index = 0;
            }
            continue;
        }

        // Handle strings (double-quoted)
        if (ch == '"')
        {
            buffer[index++] = ch; // Add the starting quote
            while ((ch = fgetc(file)) != '"' && ch != EOF)
            {
                buffer[index++] = ch; // Add content inside the string
            }
            if (ch == '"')
            {
                buffer[index++] = ch; // Add the closing quote
                buffer[index] = '\0'; // Null-terminate the string
                printf("String: %s\n", buffer);
                index = 0;
            }
            else
            {
                printf("Lexical Error: Unclosed string literal\n");
                index = 0;
            }
            continue;
        }

        // Handle punctuation
        if (is_punctuation(ch))
        {
            if (index > 0)
            {
                buffer[index] = '\0';
                if (is_keyword(buffer))
                {
                    printf("Keyword: %s\n", buffer);
                }
                else if (isdigit(buffer[0]) && !is_valid_token(buffer))
                {
                    printf("Lexical Error: Invalid lexeme %s\n", buffer);
                }
                else if (isdigit(buffer[0]))
                {
                    printf("Constant: %s\n", buffer);
                }
                else if (isalpha(buffer[0]))
                {
                    printf("Identifier: %s\n", buffer);
                    add_to_symbol_table(buffer);
                }
                else
                {
                    printf("Lexical Error: Invalid lexeme %s\n", buffer);
                }
                index = 0;
            }
            printf("Punctuation: %c\n", ch);
            continue;
        }

        // Handle operators (including shorthand operators)
        if (is_operator(ch))
        {
            buffer[index++] = ch; // Start the operator buffer
            ch = fgetc(file);     // Look at the next character

            // Check for shorthand operators like ++, +=, etc.
            if (ch == '+' || ch == '-' || ch == '=' || ch == '/' || ch == '*' || ch == '&' || ch == '|')
            {
                buffer[index++] = ch;
                char next_char = fgetc(file);
                if (next_char != ch)
                { // Make sure not a repeated operator like `+++` or `----`
                    buffer[index++] = next_char;
                    buffer[index] = '\0'; // Null-terminate the operator string

                    // Check if it's a shorthand operator
                    if (is_shorthand_operator(buffer))
                    {
                        printf("Operator: %s\n", buffer);
                    }
                    else
                    {
                        printf("Lexical Error: Invalid operator %s\n", buffer);
                    }
                    index = 0;
                    continue;
                }
                else
                {
                    ungetc(next_char, file); // Put back the character if it's not a valid shorthand operator
                }
            }
            else
            {
                ungetc(ch, file); // Put back the character if not part of shorthand operator
            }
            // Handle individual operators like +, -, etc.
            buffer[index] = '\0';
            printf("Operator: %s\n", buffer);
            index = 0;
            continue;
        }

        // Add character to buffer
        buffer[index++] = ch;
    }

    // Handle the last token
    if (index > 0)
    {
        buffer[index] = '\0';
        if (is_keyword(buffer))
        {
            printf("Keyword: %s\n", buffer);
        }
        else if (isdigit(buffer[0]) && !is_valid_token(buffer))
        {
            printf("Lexical Error: Invalid lexeme %s\n", buffer);
        }
        else if (isdigit(buffer[0]))
        {
            printf("Constant: %s\n", buffer);
        }
        else if (isalpha(buffer[0]))
        {
            printf("Identifier: %s\n", buffer);
            add_to_symbol_table(buffer);
        }
        else
        {
            printf("Lexical Error: Invalid lexeme %s\n", buffer);
        }
    }

    fclose(file);
}

int main()
{
    lexical_analyzer("BT.c");
    return 0;
}
