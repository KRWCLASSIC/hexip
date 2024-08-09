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
void handleCommand(const std::vector<std::string>& args);

#endif // COMMANDS_H
