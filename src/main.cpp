#include <iostream>
#include <fstream>
#include <string>
#include <vector>
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

    std::unordered_map<std::string, double> symbolTable;
    std::string line;
    while (getline(file, line)) {
        Lexer lexer(line);
        auto tokens = lexer.tokenize();

        Parser parser(tokens);
        auto ast = parser.parseStatement();

        if (ast) {
            double result = Eval::eval(ast.get(), symbolTable);
            std::cout << "Result: " << result << std::endl;
        }
    }

    file.close();
}
