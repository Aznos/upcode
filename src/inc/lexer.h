#ifndef LEXE_H
#define LEXER_H

#include <string>
#include <vector>

class Lexer {
    public:
        Lexer(const std::string &source);
    private:
        std::string sourceCode;
};

#endif 