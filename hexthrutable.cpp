#include "headers/hexthrutable.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <filesystem>
#include <lib/nlohmann/json.hpp>
#include <algorithm>

namespace fs = std::filesystem;
using json = nlohmann::json;

void hexThruTable(const std::string& inputFile, const std::string& outputFile) {
    // Check if hexlookuptable.json exists
    if (!fs::exists("hexlookuptable.json")) {
        std::cerr << "Error: hexlookuptable.json not found" << std::endl;
        return;
    }

    // Load the hex lookup table
    std::ifstream lookupFile("hexlookuptable.json");
    json lookupTable;
    lookupFile >> lookupTable;

    std::ifstream inFile(inputFile);
    std::ofstream outFile(outputFile);

    if (!inFile || !outFile) {
        std::cerr << "Error: Unable to open input or output file" << std::endl;
        return;
    }

    std::string line;
    bool isHexData = false;
    std::stringstream convertedData;

    while (std::getline(inFile, line)) {
        if (line.substr(0, 6) == "File: ") {
            if (isHexData) {
                outFile << convertedData.str() << std::endl << std::endl;
                convertedData.str("");
                isHexData = false;
            }
            outFile << line << std::endl;
        } else if (line.find('-') != std::string::npos) {
            outFile << line << std::endl;
            isHexData = true;
        } else if (isHexData && !line.empty()) {
            std::string hexValue = line.substr(0, 2);
            std::transform(hexValue.begin(), hexValue.end(), hexValue.begin(), ::toupper);
            if (lookupTable.contains(hexValue)) {
                std::string charValue = lookupTable[hexValue];
                // Remove surrounding quotes if present
                if (charValue.size() >= 2 && charValue.front() == '"' && charValue.back() == '"') {
                    charValue = charValue.substr(1, charValue.size() - 2);
                }
                convertedData << charValue;
            } else {
                convertedData << "?";
            }
        }
    }

    // Write any remaining converted data
    if (isHexData) {
        outFile << convertedData.str() << std::endl;
    }

    std::cout << "Conversion complete. Output written to " << outputFile << std::endl;
}