//
// Created by bnorb on 12.01.20.
//

#include <fstream>
#include <iostream>
#include <string>
#include <vector>

bool parse(const std::vector<std::string>& inputVector);
bool parseLine(const std::string& line);
bool readFile(const std::string &filePath, std::vector<std::string> &inputVector);
bool writeFile(const std::string &filePath, const std::vector<std::string> &outputVector);

int main() {
    std::vector<std::string> inputVector;
    readFile("../picture.ppm", inputVector);

    parse(inputVector);

    writeFile("../picture2.ppm", inputVector);
}

bool parse(const std::vector<std::string>& inputVector) {
    for (const auto& s : inputVector) {
        if (!parseLine(s))
            return false;
    }
    return true;
}

bool parseLine(const std::string &line) {

    return true;
}


bool readFile(const std::string &filePath, std::vector<std::string> &inputVector) {
    std::ifstream infile(filePath);

    if(!infile) {
        std::cerr << "Cannot open input file." << std::endl;
        return false;
    }

    std::string line;
    while (std::getline(infile, line)) {
        std::cout << line << std::endl;
        inputVector.push_back(line);
    }
    return true;
}


bool writeFile(const std::string &filePath, const std::vector<std::string> &outputVector) {
    std::ofstream outFile(filePath);

    if(!outFile) {
        std::cerr << "Cannot open output file." << std::endl;
        return false;
    }

    for (const std::string& s : outputVector) {
        outFile << s << std::endl;
    }

    return true;
}