#include "lexer.h"

Lexer::Lexer(const std::string &source) : sourceCode(source), currentPos(0) {}

std::vector<Token> Lexer::tokenize() {
    std::vector<Token> tokens;
    Token token;

    do {
        token = getNextToken();
        tokens.push_back(token);
    } while(token.type != TokenType::EndOfLine);

    return tokens;
}