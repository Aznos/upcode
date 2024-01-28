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
        std::vector<Token> tokenize();
    private:
        std::string sourceCode;
        size_t currentPos = 0;

        Token getNextToken();
        bool isDigit(char c);
        Token extractNumber();
};

#endif 