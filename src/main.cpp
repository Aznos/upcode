#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include "inc/parser.h"

int main(int argc, char* argv[]) {
    if(argc < 2) {
        std::cerr << "Usage" << argv[0] << " <filename>.up" << std::endl;
        return 1;
    }

    std::ifstream file(argv[1]);
    if(!file.is_open()) {
        std::cerr << "Failed to open file: " << argv[1] << std::endl;
        return 1;
    }

    std::vector<std::string> lines;
    std::string line;
    while(getline(file, line)) {
        lines.push_back(line);
    }
    file.close();

    std::reverse(lines.begin(), lines.end());

    for(const auto &reversedLine : lines) {
        try {
            Lexer lexer(reversedLine);
            auto tokens = lexer.tokenize();

            Parser parser(tokens);
            double result = parser.parseExpression();
            std::cout << "Result: " << result << std::endl;
        } catch(const std::runtime_error &e) {
            std::cerr << "Error: " << e.what() << std::endl;
            break;
        }
    }
}