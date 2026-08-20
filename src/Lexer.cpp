#include "Lexer.h"

#include <cctype>

using namespace std;

Lexer::Lexer(const string& sourceCode)
    : source(sourceCode), position(0), line(1) {}


bool Lexer::isKeyword(const string& word) {

    const string keywords[] = {

        "int",
        "float",
        "double",
        "char",
        "void",
        "return",

        "if",
        "else",
        "for",
        "while",

        "using",
        "namespace",

        "include",

        "const",
        "static"
    };

    for (const string& keyword : keywords) {

        if (word == keyword)
            return true;
    }

    return false;
}


bool Lexer::isMathFunction(const string& word) {

    const string functions[] = {

        "sqrt",
        "pow",
        "abs",
        "sin",
        "cos",
        "tan",
        "log",
        "log10",
        "ceil",
        "floor",
        "exp",
        "round",
        "fabs"
    };

    for (const string& function : functions) {

        if (word == function)
            return true;
    }

    return false;
}


bool Lexer::isOperator(char c) {

    return c == '+' ||
           c == '-' ||
           c == '*' ||
           c == '/' ||
           c == '=' ||
           c == '<' ||
           c == '>' ||
           c == '!' ||
           c == '&' ||
           c == '|';
}


bool Lexer::isSymbol(char c) {

    return c == ';' ||
           c == ',' ||
           c == '(' ||
           c == ')' ||
           c == '{' ||
           c == '}' ||
           c == '[' ||
           c == ']';
}


vector<Token> Lexer::tokenize() {

    vector<Token> tokens;

    while (position < (int)source.length()) {

        char current = source[position];


        // -----------------------------
        // Spaces
        // -----------------------------

        if (isspace(current)) {

            if (current == '\n')
                line++;

            position++;

            continue;
        }


        // -----------------------------
        // Comments
        // -----------------------------

        if (current == '/' &&
            position + 1 < (int)source.length()) {

            // Single-line comment
            if (source[position + 1] == '/') {

                while (position < (int)source.length() &&
                       source[position] != '\n') {

                    position++;
                }

                continue;
            }

            // Multi-line comment
            if (source[position + 1] == '*') {

                position += 2;

                while (position + 1 < (int)source.length()) {

                    if (source[position] == '\n')
                        line++;

                    if (source[position] == '*' &&
                        source[position + 1] == '/') {

                        position += 2;

                        break;
                    }

                    position++;
                }

                continue;
            }
        }


        // -----------------------------
        // Preprocessor
        // -----------------------------

        if (current == '#') {

            string value;

            while (position < (int)source.length() &&
                   source[position] != '\n') {

                value += source[position];

                position++;
            }

            tokens.emplace_back(
                TokenType::PREPROCESSOR,
                value,
                line
            );

            continue;
        }


        // -----------------------------
        // Identifier / Keyword / Function
        // -----------------------------

        if (isalpha(current) || current == '_') {

            string word;

            while (position < (int)source.length() &&
                   (isalnum(source[position]) ||
                    source[position] == '_')) {

                word += source[position];

                position++;
            }


            if (isMathFunction(word)) {

                tokens.emplace_back(
                    TokenType::FUNCTION,
                    word,
                    line
                );
            }

            else if (isKeyword(word)) {

                tokens.emplace_back(
                    TokenType::KEYWORD,
                    word,
                    line
                );
            }

            else {

                tokens.emplace_back(
                    TokenType::IDENTIFIER,
                    word,
                    line
                );
            }

            continue;
        }


        // -----------------------------
        // Number
        // -----------------------------

        if (isdigit(current)) {

            string number;

            bool hasDot = false;

            while (position < (int)source.length() &&
                   (isdigit(source[position]) ||
                    source[position] == '.')) {

                if (source[position] == '.') {

                    if (hasDot)
                        break;

                    hasDot = true;
                }

                number += source[position];

                position++;
            }

            tokens.emplace_back(
                TokenType::NUMBER,
                number,
                line
            );

            continue;
        }


        // -----------------------------
        // String
        // -----------------------------

        if (current == '"') {

            string value;

            value += current;

            position++;

            while (position < (int)source.length()) {

                char c = source[position];

                value += c;

                position++;

                if (c == '\\' &&
                    position < (int)source.length()) {

                    value += source[position];

                    position++;

                    continue;
                }

                if (c == '"')
                    break;
            }

            tokens.emplace_back(
                TokenType::STRING_LITERAL,
                value,
                line
            );

            continue;
        }


        // -----------------------------
        // Operators
        // -----------------------------

        if (isOperator(current)) {

            string op;

            op += current;

            position++;

            if (position < (int)source.length()) {

                char next = source[position];

                if ((current == '=' && next == '=') ||
                    (current == '>' && next == '=') ||
                    (current == '<' && next == '=') ||
                    (current == '!' && next == '=') ||
                    (current == '+' && next == '+') ||
                    (current == '-' && next == '-') ||
                    (current == '&' && next == '&') ||
                    (current == '|' && next == '|')) {

                    op += next;

                    position++;
                }
            }

            tokens.emplace_back(
                TokenType::OPERATOR,
                op,
                line
            );

            continue;
        }


        // -----------------------------
        // Symbols
        // -----------------------------

        if (isSymbol(current)) {

            string symbol;

            symbol += current;

            tokens.emplace_back(
                TokenType::SYMBOL,
                symbol,
                line
            );

            position++;

            continue;
        }


        // -----------------------------
        // Unknown
        // -----------------------------

        string unknown;

        unknown += current;

        tokens.emplace_back(
            TokenType::UNKNOWN,
            unknown,
            line
        );

        position++;
    }

    return tokens;
}


string tokenTypeToString(TokenType type) {

    switch (type) {

        case TokenType::KEYWORD:
            return "KEYWORD";

        case TokenType::IDENTIFIER:
            return "IDENTIFIER";

        case TokenType::FUNCTION:
            return "MATH_FUNCTION";

        case TokenType::NUMBER:
            return "NUMBER";

        case TokenType::STRING_LITERAL:
            return "STRING";

        case TokenType::OPERATOR:
            return "OPERATOR";

        case TokenType::SYMBOL:
            return "SYMBOL";

        case TokenType::PREPROCESSOR:
            return "PREPROCESSOR";

        default:
            return "UNKNOWN";
    }
}