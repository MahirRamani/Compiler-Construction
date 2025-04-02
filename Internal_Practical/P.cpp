#include <iostream>
#include <stack>
#include <string>
#include <cctype>

using namespace std;

bool isMatchingPair(char opening, char closing)
{
    return (opening == '(' && closing == ')') || 
           (opening == '{' && closing == '}') || 
           (opening == '[' && closing == ']');
}

bool isBalanced(const string expr)
{
    stack<char> s;

    for (char ch : expr)
    {
        if (ch == '(' || ch == '{' || ch == '[')
        {
            s.push(ch);
        }
        else if (ch == ')' || ch == '}' || ch == ']')
        {
            if (s.empty() || !isMatchingPair(s.top(), ch))
            {
                return false;
            }
            s.pop();
        }
    }
    return s.empty();
}

void tokenize(const string expr)
{
    cout << "Tokens: " << endl;
    string token = "";
    
    for (size_t i = 0; i < expr.length(); i++)
    {
        char ch = expr[i];

        // Skip whitespace
        if (isspace(ch))
        {
            continue;
        }

        // Check if it's a number (integer or float)
        if (isdigit(ch) || (ch == '.' && i + 1 < expr.length() && isdigit(expr[i + 1])))
        {
            token += ch;
            while (i + 1 < expr.length() && (isdigit(expr[i + 1]) || expr[i + 1] == '.'))
            {
                token += expr[++i];
            }
            cout << "Number: " << token << endl;
            token = "";
        }
        // Check if it's an identifier (variable or function name)
        else if (isalpha(ch))
        {
            token += ch;
            while (i + 1 < expr.length() && (isalnum(expr[i + 1]) || expr[i + 1] == '_'))
            {
                token += expr[++i];
            }
            cout << "Identifier: " << token << endl;
            token = "";
        }
        // Check for operators
        else if (string("+-*/%^=").find(ch) != string::npos)
        {
            cout << "Operator: " << ch << endl;
        }
        // Check for parentheses, brackets, and braces
        else if (string("(){}[]").find(ch) != string::npos)
        {
            cout << "Parenthesis/Brace: " << ch << endl;
        }
        // Other symbols (e.g., commas, semicolons)
        else
        {
            cout << "Symbol: " << ch << endl;
        }
    }
}

int main()
{
    string expr;
    cout << "Enter an expression: ";
    getline(cin, expr);

    tokenize(expr);

    if (isBalanced(expr))
    {
        cout << "Balanced Parentheses." << endl;
    }
    else
    {
        cout << "Unbalanced Parentheses." << endl;
    }

    return 0;
}

// #include <iostream>
// #include <stack>
// #include <string>

// using namespace std;

// bool isMatchingPair(char opening, char closing)
// {
//     return (opening == '(' && closing == ')') || (opening == '{' && closing == '}') || (opening == '[' && closing == ']');
// }

// bool isBalanced(const string expr)
// {
//     stack<char> s;

//     for (char ch : expr)
//     {
//         if (ch == '(' || ch == '{' || ch == '[')
//         {
//             s.push(ch);
//         }
//         else if (ch == ')' || ch == '}' || ch == ']')
//         {
//             if (s.empty() || !isMatchingPair(s.top(), ch))
//             {
//                 return false;
//             }
//             s.pop();
//         }
//     }
//     return s.empty();
// }

// void tokenize(const string expr)
// {
//     cout << "Tokens: ";
//     for (char ch : expr)
//     {
//         if (ch != ' ')
//         {
//             cout << ch << " ";
//         }
//     }
//     cout << endl;
// }

// int main()
// {
//     string expr;
//     cout << "Enter an expression: ";
//     getline(cin, expr);

//     tokenize(expr);

//     if (isBalanced(expr))
//     {
//         cout << "Balanced Parentheses." << endl;
//     }
//     else
//     {
//         cout << "Unbalanced Parentheses." << endl;
//     }

//     return 0;
// }