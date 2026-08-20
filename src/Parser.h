#ifndef PARSER_H
#define PARSER_H

#include "Token.h"
#include "SymbolTable.h"

#include <vector>

class Parser {

private:

    std::vector<Token> tokens;

    SymbolTable symbolTable;

    bool checkBrackets();

    bool checkMathFunctions();

    bool checkSemicolons();

public:

    Parser(const std::vector<Token>& tokenList);

    bool analyze();

    bool displayResult();

    void displaySymbolTable();
};

#endif