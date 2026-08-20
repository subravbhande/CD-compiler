#ifndef TOKEN_H
#define TOKEN_H

#include <string>

enum class TokenType {
    KEYWORD,
    IDENTIFIER,
    FUNCTION,
    NUMBER,
    STRING_LITERAL,
    OPERATOR,
    SYMBOL,
    PREPROCESSOR,
    UNKNOWN
};

struct Token {

    TokenType type;
    std::string value;
    int line;

    Token(TokenType t, const std::string& v, int l)
        : type(t), value(v), line(l) {}
};

std::string tokenTypeToString(TokenType type);

#endif