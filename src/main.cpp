#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

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

    std::cout << "hello world!" << std::endl;
}