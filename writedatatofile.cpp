#include "headers/commands.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <filesystem>
#include <iomanip>

namespace fs = std::filesystem;

void writeDataToFile(const std::string& input) {
    std::vector<std::string> files;
    
    if (fs::is_directory(input)) {
        for (const auto& entry : fs::directory_iterator(input)) {
            files.push_back(entry.path().string());
        }
    } else {
        std::istringstream iss(input);
        std::string file;
        while (std::getline(iss, file, ',')) {
            files.push_back(file);
        }
    }

    std::ofstream outFile("output.txt");
    if (!outFile) {
        std::cerr << "Error: Unable to create output file." << std::endl;
        return;
    }

    for (const auto& file : files) {
        std::ifstream inFile(file, std::ios::binary);
        if (!inFile) {
            std::cerr << "Error: Unable to open file " << file << std::endl;
            continue;
        }

        outFile << "File: " << file << std::endl;
        outFile << std::string(80, '-') << std::endl;

        char byte;
        while (inFile.get(byte)) {
            outFile << std::setfill('0') << std::setw(2) << std::hex << (int)(unsigned char)byte << std::endl;
        }

        outFile << std::endl << std::endl;
    }

    std::cout << "Data written to output.txt" << std::endl;
}