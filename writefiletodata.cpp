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
            fs::path filePath(currentFile);
            std::cout << "Attempting to create directory: " << filePath.parent_path() << std::endl;
            try {
                if (!fs::exists(filePath.parent_path())) {
                    if (!fs::create_directories(filePath.parent_path())) {
                        std::cerr << "Error: Failed to create directory for " << currentFile << std::endl;
                        std::cerr << "Directory path: " << filePath.parent_path() << std::endl;
                        continue;
                    }
                }
            } catch (const fs::filesystem_error& e) {
                std::cerr << "Error: Unable to create directory for " << currentFile << std::endl;
                std::cerr << "Filesystem error: " << e.what() << std::endl;
                std::cerr << "Error code: " << e.code().value() << " - " << e.code().message() << std::endl;
                continue;
            }
            outFile.open(currentFile, std::ios::binary);
            if (!outFile) {
                std::cerr << "Error: Unable to create output file " << currentFile << std::endl;
                continue;
            }
            std::cout << "Creating file: " << currentFile << std::endl;
            std::getline(inFile, line); // Skip the dashed line
        } else if (line.substr(0, 10) == "EmptyDir: ") {
            std::string dirPath = line.substr(10);
            try {
                fs::create_directories(dirPath);
                std::cout << "Creating empty directory: " << dirPath << std::endl;
            } catch (const fs::filesystem_error& e) {
                std::cerr << "Error: Unable to create empty directory " << dirPath << std::endl;
                std::cerr << "Filesystem error: " << e.what() << std::endl;
            }
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

    std::cout << "Files and directories have been created from the hex data in " << inputFile << std::endl;
}