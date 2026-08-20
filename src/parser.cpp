#include "Parser.h"

#include <iostream>
#include <stack>

using namespace std;


Parser::Parser(
    const vector<Token>& tokenList
) : tokens(tokenList) {}


// ==========================================
// BRACKET CHECKING
// ==========================================

bool Parser::checkBrackets() {

    stack<string> brackets;

    for (const Token& token : tokens) {

        if (token.value == "(" ||
            token.value == "{" ||
            token.value == "[") {

            brackets.push(token.value);
        }

        else if (token.value == ")" ||
                 token.value == "}" ||
                 token.value == "]") {

            if (brackets.empty())
                return false;

            string opening = brackets.top();

            brackets.pop();

            if (token.value == ")" &&
                opening != "(")
                return false;

            if (token.value == "}" &&
                opening != "{")
                return false;

            if (token.value == "]" &&
                opening != "[")
                return false;
        }
    }

    return brackets.empty();
}


// ==========================================
// MATH FUNCTION CHECKING
// ==========================================

bool Parser::checkMathFunctions() {

    for (size_t i = 0; i < tokens.size(); i++) {

        if (tokens[i].type ==
            TokenType::FUNCTION) {

            // Next token should be '('

            if (i + 1 >= tokens.size())
                return false;

            if (tokens[i + 1].value != "(") {

                cout << "\nSyntax Error: "
                     << "Expected '(' after function "
                     << tokens[i].value
                     << "\n";

                return false;
            }
        }
    }

    return true;
}


// ==========================================
// SEMICOLON CHECKING
// ==========================================

bool Parser::checkSemicolons() {

    for (size_t i = 0; i < tokens.size(); i++) {

        if (tokens[i].value == "int" ||
            tokens[i].value == "float" ||
            tokens[i].value == "double" ||
            tokens[i].value == "char" ||
            tokens[i].value == "return") {

            // Skip function definitions:
            // type name(...) {

            if (tokens[i].value != "return" &&
                i + 2 < tokens.size() &&
                tokens[i + 1].type ==
                    TokenType::IDENTIFIER &&
                tokens[i + 2].value == "(") {

                continue;
            }

            bool found = false;

            for (size_t j = i + 1;
                 j < tokens.size();
                 j++) {

                if (tokens[j].value == ";") {

                    found = true;

                    break;
                }

                if (tokens[j].value == "{") {

                    break;
                }
            }

            if (!found)
                return false;
        }
    }

    return true;
}


// ==========================================
// ANALYSIS
// ==========================================

bool Parser::analyze() {

    if (!checkBrackets()) {

        cout << "\nSyntax Error: "
             << "Unbalanced brackets.\n";

        return false;
    }


    if (!checkMathFunctions()) {

        return false;
    }


    if (!checkSemicolons()) {

        cout << "\nSyntax Error: "
             << "Missing semicolon.\n";

        return false;
    }

    return true;
}


// ==========================================
// DISPLAY RESULT
// ==========================================

bool Parser::displayResult() {

    cout << "\n========== SYNTAX ANALYSIS ==========\n";

    bool result = analyze();

    if (result) {

        cout << "Syntax Analysis Successful.\n";
    }

    else {

        cout << "Syntax Analysis Failed.\n";
    }

    return result;
}


// ==========================================
// SYMBOL TABLE
// ==========================================

void Parser::displaySymbolTable() {

    for (size_t i = 0; i + 1 < tokens.size(); i++) {

        if (tokens[i].type == TokenType::KEYWORD) {

            string type = tokens[i].value;

            if (type == "int" ||
                type == "float" ||
                type == "double" ||
                type == "char") {

                if (tokens[i + 1].type ==
                    TokenType::IDENTIFIER) {

                    // Skip function declarations
                    // (name followed by '(')

                    if (i + 2 < tokens.size() &&
                        tokens[i + 2].value == "(") {

                        continue;
                    }

                    symbolTable.insert(
                        tokens[i + 1].value,
                        type
                    );
                }
            }
        }
    }

    symbolTable.display();
}