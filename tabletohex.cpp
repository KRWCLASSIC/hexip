#include "headers/tabletohex.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <filesystem>
#include <lib/nlohmann/json.hpp>
#include <string>
#include <locale>
#include <codecvt>

namespace fs = std::filesystem;
using json = nlohmann::json;

void tableToHex(const std::string& inputFile, const std::string& outputFile) {
    if (!fs::exists("reversed_hexlookuptable.json")) {
        std::cerr << "Error: reversed_hexlookuptable.json not found" << std::endl;
        return;
    }

    std::ifstream lookupFile("reversed_hexlookuptable.json");
    if (!lookupFile.is_open()) {
        std::cerr << "Error: Unable to open reversed_hexlookuptable.json" << std::endl;
        return;
    }

    json lookupTable;
    lookupFile >> lookupTable;

    std::ifstream inFile(inputFile, std::ios::binary);
    std::ofstream outFile(outputFile);

    if (!inFile || !outFile) {
        std::cerr << "Error: Unable to open input or output file" << std::endl;
        return;
    }

    std::string line;
    bool isData = false;

    while (std::getline(inFile, line)) {
        line.erase(std::remove(line.begin(), line.end(), '\r'), line.end());

        if (line.substr(0, 6) == "File: ") {
            outFile << line << std::endl;
            isData = false;
        } else if (line.find('-') != std::string::npos) {
            outFile << line << std::endl;
            isData = true;
        } else if (isData && !line.empty()) {
            for (char c : line) {
                std::string charValue(1, c);
                
                // Check if character is in lookup table
                if (lookupTable.contains(charValue)) {
                    outFile << lookupTable[charValue]; // Write hex value to output
                } else {
                    outFile << "?"; // Handle unknown characters
                    std::cerr << "Warning: Character '" << charValue << "' not found in lookup table." << std::endl;
                }
            }
            outFile << std::endl;
        }
    }

    std::cout << "Conversion complete. Output written to " << outputFile << std::endl;
}
