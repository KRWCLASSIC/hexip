// commands.h
#ifndef COMMANDS_H
#define COMMANDS_H

#include <vector>
#include <string>

void printHelp();
void handleMetadataCommand(const std::vector<std::string>& args);
void handleArchiveCommand(const std::vector<std::string>& args);
void handleSecurityCommand(const std::vector<std::string>& args);
void handleHashCommand(const std::vector<std::string>& args);
void handleWriteDataToFile(const std::vector<std::string>& args);
void handleWriteFileToData(const std::vector<std::string>& args);
void handleCommand(const std::vector<std::string>& args);
void tableToHex(const std::string& inputFile, const std::string& outputFile);
void tableToHexCommand(const std::string& input);

#endif // COMMANDS_H