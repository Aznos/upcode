#ifndef PARSER_H
#define PARSER_H

#include "lexer.h"
#include <vector>
#include <memory>

class Parser {
    public:
        explicit Parser(const std::vector<Token> &tokens);
    private:
        std::vector<Token> tokens;
        size_t currentTokenIndex;

        const Token &currentToken() const;
        void advanceToken();
};

#endif