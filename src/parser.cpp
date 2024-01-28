#include "parser.h"
#include <stdexcept>
#include <cmath>

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

std::unique_ptr<ASTNode> Parser::parseExpression() {
    auto node = parseTerm();

    while (currentToken().type == TokenType::Operator &&
           (currentToken().text == "+" || currentToken().text == "-")) {
        char op = currentToken().text[0];
        advanceToken();
        node = std::make_unique<BinaryOpNode>(op, std::move(node), parseTerm());
    }

    return node;
}

std::unique_ptr<ASTNode> Parser::parseTerm() {
    auto node = parseFactor();

    while(currentToken().type == TokenType::Operator &&
        (currentToken().text == "*" || currentToken().text == "/"))
    
    char op = currentToken().text[0];
    advanceToken();
    node = std::make_unique<BinaryOpNode>(op, std::move(node), parseFactor());

    return node;
}

std::unique_ptr<ASTNode> Parser::parseFactor() {
    if(currentToken().type == TokenType::Number) {
        double value = std::stod(currentToken().text);
        advanceToken();
        return std::make_unique<NumberNode>(value);
    } else if(currentToken().text == "(") {
        advanceToken();
        auto node = parseExpression();
        if(currentToken().text != ")") {
            throw std::runtime_error("Expected ')");
        }
        advanceToken();
        return node;
    } else {
        throw std::runtime_error("Unexpected token: " + currentToken().text);
    }
}