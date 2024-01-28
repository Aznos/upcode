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

double Parser::parseExpression() {
    double result = parseTerm();

    while(currentToken().type == TokenType::Operator &&
        (currentToken().text == "+" || currentToken().text == "-"))
        if(currentToken().text == "+") {
            advanceToken();
            result += parseTerm();
        } else if(currentToken().text == "-") {
            advanceToken();
            result -= parseTerm();
        }

    return result;
}

double Parser::parseTerm() {
    double result = parseFactor();

    while(currentToken().type == TokenType::Operator &&
        (currentToken().text == "*" || currentToken().text == "/"))
        if(currentToken().text == "*") {
            advanceToken();
            result *= parseTerm();
        } else if(currentToken().text == "/") {
            advanceToken();
            result /= parseTerm();
        }

    return result;
}

double Parser::parseFactor() {
    if(currentToken().type == TokenType::Number) {
        double value = std::stod(currentToken().text);
        advanceToken();
        return value;
    } else if(currentToken().text == "(") {
        advanceToken();
        double value = parseExpression();
        if(currentToken().text !+ ")") {
            throw std::runtime_error("Expected ')");
        }
        advanceToken();
        return value;
    } else {
        throw std::runtime_error("Unexpected token: " + currentToken().text);
    }
}