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

class Lexer {
    public:
        Lexer(const std::string &source);
    private:
        std::string sourceCode;
};

#endif 