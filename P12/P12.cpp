#include <iostream>
#include <sstream>
#include <stack>
#include <vector>
#include <cctype>
#include <map>
#include <cmath>
#include <string>

using namespace std;

// Function to check if a string is a number
bool isNumber(const string &s) {
    if (s.empty()) return false;
    
    char* end = nullptr;
    strtod(s.c_str(), &end);
    return end != s.c_str() && *end == '\0';
}

// Function to check if a string is a variable
bool isVariable(const string &s) {
    if (s.empty()) return false;
    return isalpha(s[0]);
}

// Function to apply an operation to two numbers
double applyOperation(double a, double b, char op) {
    switch (op) {
        case '+': return a + b;
        case '-': return a - b;
        case '*': return a * b;
        case '/': return (b != 0) ? a / b : 0;
        default: return 0;
    }
}

// Function to determine operator precedence
int precedence(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    return 0;
}

// Function to tokenize the input expression
vector<string> tokenize(const string &expr) {
    vector<string> tokens;
    string current;
    
    for (size_t i = 0; i < expr.size(); ++i) {
        char c = expr[i];
        
        if (isspace(c)) {
            if (!current.empty()) {
                tokens.push_back(current);
                current.clear();
            }
        } else if (c == '+' || c == '-' || c == '*' || c == '/' || c == '(' || c == ')') {
            if (!current.empty()) {
                tokens.push_back(current);
                current.clear();
            }
            tokens.push_back(string(1, c));
        } else {
            current += c;
        }
    }
    
    if (!current.empty()) {
        tokens.push_back(current);
    }
    
    return tokens;
}

// Function to convert infix to postfix (Shunting Yard Algorithm)
vector<string> infixToPostfix(const vector<string> &tokens) {
    stack<string> opStack;
    vector<string> output;
    
    for (const string &token : tokens) {
        if (isNumber(token) || isVariable(token)) {
            output.push_back(token);
        } else if (token == "(") {
            opStack.push(token);
        } else if (token == ")") {
            while (!opStack.empty() && opStack.top() != "(") {
                output.push_back(opStack.top());
                opStack.pop();
            }
            if (!opStack.empty() && opStack.top() == "(") {
                opStack.pop(); // Discard the left parenthesis
            }
        } else {  // Operator
            while (!opStack.empty() && opStack.top() != "(" && 
                   precedence(token[0]) <= precedence(opStack.top()[0])) {
                output.push_back(opStack.top());
                opStack.pop();
            }
            opStack.push(token);
        }
    }
    
    // Pop remaining operators
    while (!opStack.empty()) {
        if (opStack.top() != "(") {
            output.push_back(opStack.top());
        }
        opStack.pop();
    }
    
    return output;
}

// Helper function to format numeric output (remove trailing zeros)
string formatNumber(double num) {
    // Check if number is essentially an integer
    if (fabs(num - round(num)) < 1e-10) {
        return to_string(static_cast<int>(round(num)));
    }
    
    string str = to_string(num);
    
    // Remove trailing zeros
    str.erase(str.find_last_not_of('0') + 1, string::npos);
    if (str.back() == '.') {
        str.pop_back();
    }
    
    return str;
}

// Evaluate a postfix expression with constant folding
string evaluatePostfixWithConstantFolding(const vector<string> &postfix) {
    struct Token {
        bool isConstant;
        double value;
        string expr;
        
        Token(double v) : isConstant(true), value(v), expr(formatNumber(v)) {}
        Token(const string &e) : isConstant(false), value(0), expr(e) {}
    };
    
    stack<Token> stk;
    
    for (const string &token : postfix) {
        if (isNumber(token)) {
            stk.push(Token(stod(token)));
        } else if (isVariable(token)) {
            stk.push(Token(token));
        } else if (token.size() == 1 && string("+-*/").find(token[0]) != string::npos) {
            if (stk.size() < 2) continue;
            
            Token b = stk.top(); stk.pop();
            Token a = stk.top(); stk.pop();
            
            if (a.isConstant && b.isConstant) {
                // Both operands are constants, compute the result
                double result = applyOperation(a.value, b.value, token[0]);
                stk.push(Token(result));
            } else {
                // At least one operand is a variable expression
                string newExpr;
                
                // Handle operator precedence with parentheses
                if (!a.isConstant && token[0] != '+' && token[0] != '-' && 
                    (a.expr.find('+') != string::npos || a.expr.find('-') != string::npos)) {
                    newExpr = "(" + a.expr + ")";
                } else {
                    newExpr = a.expr;
                }
                
                newExpr += " " + token + " ";
                
                if (!b.isConstant && token[0] != '+' && 
                    (b.expr.find('+') != string::npos || b.expr.find('-') != string::npos)) {
                    newExpr += "(" + b.expr + ")";
                } else {
                    newExpr += b.expr;
                }
                
                stk.push(Token(newExpr));
            }
        }
    }
    
    return stk.empty() ? "" : stk.top().expr;
}

// Function to optimize an arithmetic expression
string optimizeExpression(const string &expr) {
    vector<string> tokens = tokenize(expr);
    vector<string> postfix = infixToPostfix(tokens);
    return evaluatePostfixWithConstantFolding(postfix);
}

int main() {
    string expr;
    
    cout << "Constant Folding Optimizer" << endl;
    cout << "Enter an arithmetic expression to optimize (or 'quit' to exit):" << endl;
    
    while (true) {
        cout << "Expression: ";
        getline(cin, expr);
        
        if (expr == "quit") {
            break;
        }
        
        string optimized = optimizeExpression(expr);
        cout << "Optimized: " << optimized << endl;
    }
    
    return 0;
}