#ifndef LEXER_H
#define LEXER_H
#include "Token.h"
#include <string>
#include <vector>

class Lexer {

private:

    std::string source;
    int position;
    int line;

    bool isKeyword(const std::string& word);
    bool isMathFunction(const std::string& word);

    bool isOperator(char c);
    bool isSymbol(char c);

public:

    Lexer(const std::string& sourceCode);

    std::vector<Token> tokenize();
};

#endif