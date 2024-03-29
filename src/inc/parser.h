#ifndef PARSER_H
#define PARSER_H

#include "lexer.h"
#include "ast.h"
#include <vector>
#include <memory>

class Parser {
    public:
        explicit Parser(const std::vector<Token> &tokens);
        std::unique_ptr<ASTNode> parseExpression();
        std::unique_ptr<ASTNode> parseStatement();
    private:
        std::vector<Token> tokens;
        size_t currentTokenIndex;

        const Token &currentToken() const;
        void advanceToken();

        std::unique_ptr<ASTNode> parseTerm();
        std::unique_ptr<ASTNode> parseFactor();
        std::unique_ptr<ASTNode> parseVariableDeclaration();
        std::unique_ptr<ASTNode> parseVariableUsage();
};

#endif