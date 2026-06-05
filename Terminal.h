#ifndef TERMINAL_H
#define TERMINAL_H
#include <string>
#include <vector>
#include <memory>
#include "Directory.h"
#include "Entry.h"
class Terminal {
private:
std::unique_ptr<Directory> root;
Directory* currentDir;
std::vector<std::unique_ptr<Entry>> hiddenEntries;
std::string getPrompt() const;
void processCommand(const std::string& command);
void showHelp();
void handleCd(std::istringstream& iss);
void handleCat(std::istringstream& iss);
void handleTouch(std::istringstream& iss);
void handleMkdir(std::istringstream& iss);
void handleRm(std::istringstream& iss);
void handleRestore(std::istringstream& iss);
void handleMv(std::istringstream& iss);
void handleEdit(std::istringstream& iss);
public:
Terminal();
void run();
};
#endif
