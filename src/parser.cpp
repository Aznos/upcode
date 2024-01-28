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

    while (currentToken().type == TokenType::Operator &&
           (currentToken().text == "*" || currentToken().text == "/")) {
        char op = currentToken().text[0];
        advanceToken();
        node = std::make_unique<BinaryOpNode>(op, std::move(node), parseFactor());
    }

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

std::unique_ptr<ASTNode> Parser::parseStatement() {
    if(currentToken().type == TokenType::Const) {
        return parseVariableDeclaration();
    }

    return nullptr;
}

std::unique_ptr<ASTNode> Parser::parseVariableDeclaration() {
    advanceToken();
    if(currentToken().type != TokenType::Identifier) {
        throw std::runtime_error("Expected variable name");
    }

    std::string varName = currentToken().text;
    advanceToken();

    if(currentToken().type != TokenType::Equal) {
        throw std::runtime_error("Expected '=' after variable name");
    }
    advanceToken();

    auto expression = parseExpression();

    if(currentToken().type != TokenType::Semicolon) {
        throw std::runtime_error("Expected ';' after variable declaration");
    }

    advanceToken();

    return std::make_unique<VariableDeclarationNode>(varName, std::move(expression));
}

std::unique_ptr<ASTNode> Parser::parseVariableUsage() {
    std::string varName = currentToken().text;
    advanceToken();
    return std::make_unique<VariableUsageNode>(varName);
}