#ifndef LEXE_H
#define LEXER_H

#include <string>
#include <vector>

enum class TokenType {
    Number,
    Operator,
    OpenParen,
    CloseParen,
    EndOfLine
};

struct Token {
    TokenType type;
    std::string text;
};

class Lexer {
    public:
        Lexer(const std::string &source);
    private:
        std::string sourceCode;
};

#endif 