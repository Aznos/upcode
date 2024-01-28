#include "parser.h"
#include <stdexcept>

Parser::Parser(const std::vector<Token>& tokens) : tokens(tokens), currentTokenIndex(0) {}

const Token &Parser::currentToken() const {
    if(currentTokenIndex < tokens.size()) {
        return tokens[currentTokenIndex];
    }

    static Token eofToken = {TokenType::EndOfLine, ""};
    return eofToken;
}

void Parser::advanceToken() {
    if(currentTokenIndex < tokens.size()) {
        currentTokenIndex++;
    }
}