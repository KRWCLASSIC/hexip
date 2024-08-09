// main.cpp
#include "headers/commands.h"
#include <vector>
#include <string>
#include <iostream>

int main(int argc, char* argv[]) {
    if (argc < 2) {
        printHelp();
        return 1;
    }

    std::vector<std::string> args(argv + 1, argv + argc);
    handleCommand(args);
    return 0;
}
