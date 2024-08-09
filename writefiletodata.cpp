#include "headers/writefiletodata.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <filesystem>

namespace fs = std::filesystem;

void writeFileToData(const std::string& inputFile) {
    std::ifstream inFile(inputFile);
    if (!inFile) {
        std::cerr << "Error: Unable to open input file " << inputFile << std::endl;
        return;
    }

    std::string line;
    std::string currentFile;
    std::ofstream outFile;

    while (std::getline(inFile, line)) {
        if (line.substr(0, 6) == "File: ") {
            if (outFile.is_open()) {
                outFile.close();
            }
            currentFile = line.substr(6);
            outFile.open(currentFile, std::ios::binary);
            if (!outFile) {
                std::cerr << "Error: Unable to create output file " << currentFile << std::endl;
                return;
            }
            std::cout << "Creating file: " << currentFile << std::endl;
            std::getline(inFile, line); // Skip the dashed line
        } else if (!line.empty() && line.find('-') == std::string::npos) {
            unsigned int byte;
            std::istringstream iss(line);
            iss >> std::hex >> byte;
            outFile.put(static_cast<char>(byte));
        }
    }

    if (outFile.is_open()) {
        outFile.close();
    }

    std::cout << "Files have been created from the hex data in " << inputFile << std::endl;
}
