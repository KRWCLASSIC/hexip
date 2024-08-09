#include "headers/commands.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <filesystem>
#include <iomanip>

namespace fs = std::filesystem;

void writeDataToFile(const std::string& input) {
    std::vector<std::string> files;
    std::vector<std::string> emptyDirs;
    
    std::istringstream iss(input);
    std::string item;
    while (std::getline(iss, item, ',')) {
        if (fs::is_directory(item)) {
            bool hasFiles = false;
            for (const auto& entry : fs::recursive_directory_iterator(item)) {
                if (fs::is_regular_file(entry)) {
                    files.push_back(entry.path().string());
                    hasFiles = true;
                }
            }
            if (!hasFiles) {
                emptyDirs.push_back(item);
            }
        } else if (fs::is_regular_file(item)) {
            files.push_back(item);
        } else {
            std::cerr << "Warning: " << item << " is not a valid file or directory." << std::endl;
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

    // Write empty directories
    for (const auto& dir : emptyDirs) {
        outFile << "EmptyDir: " << dir << std::endl;
        outFile << std::string(80, '-') << std::endl;
        outFile << std::endl << std::endl;
    }

    std::cout << "Data written to output.txt" << std::endl;
}
