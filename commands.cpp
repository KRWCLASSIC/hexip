// commands.cpp
#include "headers/commands.h"
#include <iostream>

void printHelp() {
    std::cout << "Usage: hexip <command> [options]\n";
    std::cout << "Available commands:\n";
    std::cout << "metadata [removeall | clean | add | remove | read]\n";
    std::cout << "archive [encrypt | create/pack | decrypt/unpack | test | read]\n";
    std::cout << "analyze\n";
    std::cout << "convert\n";
    std::cout << "extract\n";
    std::cout << "editor\n";
    std::cout << "security [add | remove | removeall]\n";
    std::cout << "hash [verify | calculate]\n";
    std::cout << "help\n";
}

void handleMetadataCommand(const std::vector<std::string>& args) {
    if (args.size() < 2) {
        std::cout << "Metadata command requires a subcommand.\n";
        return;
    }
    std::string subcommand = args[1];
    if (subcommand == "removeall") {
        std::cout << "Command: metadata removeall\n";
    } else if (subcommand == "clean") {
        std::cout << "Command: metadata clean\n";
    } else if (subcommand == "add") {
        std::cout << "Command: metadata add\n";
    } else if (subcommand == "remove") {
        std::cout << "Command: metadata remove\n";
    } else if (subcommand == "read") {
        std::cout << "Command: metadata read\n";
    } else {
        std::cout << "Unknown metadata subcommand.\n";
    }
}

void handleArchiveCommand(const std::vector<std::string>& args) {
    if (args.size() < 2) {
        std::cout << "Archive command requires a subcommand.\n";
        return;
    }
    std::string subcommand = args[1];
    if (subcommand == "encrypt" || subcommand == "create" || subcommand == "pack") {
        std::cout << "Command: archive " << subcommand << "\n";
    } else if (subcommand == "decrypt" || subcommand == "unpack") {
        std::cout << "Command: archive " << subcommand << "\n";
    } else if (subcommand == "test") {
        std::cout << "Command: archive test\n";
    } else if (subcommand == "read") {
        std::cout << "Command: archive read\n";
    } else {
        std::cout << "Unknown archive subcommand.\n";
    }
}

void handleSecurityCommand(const std::vector<std::string>& args) {
    if (args.size() < 2) {
        std::cout << "Security command requires a subcommand.\n";
        return;
    }
    std::string subcommand = args[1];
    if (subcommand == "add") {
        std::cout << "Command: security add\n";
    } else if (subcommand == "remove") {
        std::cout << "Command: security remove\n";
    } else if (subcommand == "removeall") {
        std::cout << "Command: security removeall\n";
    } else {
        std::cout << "Unknown security subcommand.\n";
    }
}

void handleHashCommand(const std::vector<std::string>& args) {
    if (args.size() < 2) {
        std::cout << "Hash command requires an action.\n";
        return;
    }
    std::string action = args[1];
    if (action == "verify") {
        std::cout << "Command: hash verify\n";
    } else if (action == "calculate") {
        std::cout << "Command: hash calculate\n";
    } else {
        std::cout << "Unknown hash action.\n";
    }
}

void handleCommand(const std::vector<std::string>& args) {
    if (args.empty()) {
        printHelp();
        return;
    }

    std::string command = args[0];
    
    if (command == "help") {
        printHelp();
    } else if (command == "metadata") {
        handleMetadataCommand(args);
    } else if (command == "archive") {
        handleArchiveCommand(args);
    } else if (command == "analyze") {
        std::cout << "Command: analyze\n";
    } else if (command == "convert") {
        std::cout << "Command: convert\n";
    } else if (command == "extract") {
        std::cout << "Command: extract\n";
    } else if (command == "editor") {
        std::cout << "Command: editor\n";
    } else if (command == "security") {
        handleSecurityCommand(args);
    } else if (command == "hash") {
        handleHashCommand(args);
    } else {
        std::cout << "Unknown command: " << command << "\n";
    }
}
