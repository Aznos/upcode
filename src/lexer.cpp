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

Token Lexer::getNextToken() {
    while(currentPos < sourceCode.length() && isspace(sourceCode[currentPos])) {
        currentPos++;
    }

    if(currentPos == sourceCode.length()) {
        return {TokenType::EndOfLine, ""};
    }

    char currentChar = sourceCode[currentPos];

    if(isDigit(currentChar)) {
        return extractNumber();
    }

    switch(currentChar) {
        case '+':
        case '-':
        case '*':
        case '/':
            currentPos++;
            return {TokenType::Operator, std::string(1, currentChar)};
        case '(':
            currentPos++;
            return {TokenType::OpenParen, "("};
        case ')':
            currentPos++;
            return {TokenType::CloseParen, ")"};
        default:
            //TODO: Error out
            currentPos++;
            return {TokenType::EndOfLine, ""};
    }
}