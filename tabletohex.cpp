#include "headers/tabletohex.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <filesystem>
#include <lib/nlohmann/json.hpp>
#include <algorithm>
#include <iomanip>

namespace fs = std::filesystem;
using json = nlohmann::json;

void tableToHex(const std::string& inputFile, const std::string& outputFile) {
    // Check if hexlookuptable.json exists
    if (!fs::exists("hexlookuptable.json")) {
        std::cerr << "Error: hexlookuptable.json not found" << std::endl;
        return;
    }

    // Load the hex lookup table
    std::ifstream lookupFile("hexlookuptable.json");
    json lookupTable;
    lookupFile >> lookupTable;

    // Create a reverse lookup table
    std::map<std::string, std::string> reverseLookup;
    for (const auto& [hex, character] : lookupTable.items()) {
        reverseLookup[character] = hex;
    }

    std::ifstream inFile(inputFile);
    std::ofstream outFile(outputFile);

    if (!inFile || !outFile) {
        std::cerr << "Error: Unable to open input or output file" << std::endl;
        return;
    }

    std::string line;
    bool isData = false;

    while (std::getline(inFile, line)) {
        if (line.substr(0, 6) == "File: ") {
            outFile << line << std::endl;
            isData = false;
        } else if (line.find('-') != std::string::npos) {
            outFile << line << std::endl;
            isData = true;
        } else if (isData && !line.empty()) {
            for (char c : line) {
                std::string charStr(1, c);
                if (reverseLookup.find(charStr) != reverseLookup.end()) {
                    outFile << reverseLookup[charStr] << std::endl;
                } else {
                    outFile << "??" << std::endl;
                }
            }
        }
    }

    std::cout << "Conversion complete. Output written to " << outputFile << std::endl;
}