#include <iostream>
#include <string>
#include <fstream>

std::string bindShader(std::string dir) {
    std::string ch;
    std::string result;
    std::ifstream file;
    file.open(dir);

    if (!file.is_open()) {
        std::cout << "Error! File isn't open!" << std::endl;
    }

    while (getline(file, ch)) {
        result.append(ch + "\n");
    }

    file.close();
    return result;
}