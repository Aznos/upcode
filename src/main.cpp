#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include "inc/parser.h"
#include "inc/eval.h"
#include <unordered_map>

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <filename>.up" << std::endl;
        return 1;
    }

    std::ifstream file(argv[1]);
    if (!file.is_open()) {
        std::cerr << "Failed to open file: " << argv[1] << std::endl;
        return 1;
    }

    std::vector<std::string> lines;
    std::string line;
    while (getline(file, line)) {
        lines.push_back(line);
    }
    file.close();

    std::unordered_map<std::string, double> symbolTable;

    for (const auto &line : lines) {
        std::vector<Token> lineTokens;
        Lexer lexer(line);
        auto tokens = lexer.tokenize();
        
        for (const auto &token : tokens) {
            if (token.type != TokenType::Semicolon) {
                lineTokens.push_back(token);
            } else {
                if (!lineTokens.empty()) {
                    Parser parser(lineTokens);
                    auto ast = parser.parseStatement();
                    double result = Eval::eval(ast.get(), symbolTable);
                    std::cout << "Result: " << result << std::endl;

                    lineTokens.clear();
                }
            }
        }

        if (!lineTokens.empty()) {
            Parser parser(lineTokens);
            auto ast = parser.parseStatement();
            double result = Eval::eval(ast.get(), symbolTable);
            std::cout << "Result: " << result << std::endl;
        }
    }
}
