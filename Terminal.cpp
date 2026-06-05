#include "Terminal.h"
#include "Directory.h"
#include "SingleLineFile.h"
#include "MultiLineFile.h"
#include "Entry.h"
#include <sstream>
#include <iostream>
#include <memory>
Terminal::Terminal() {
root = std::make_unique<Directory>("root");
currentDir = root.get();
}
void Terminal::run() {
std::cout << "Virtual Terminal started. Type 'help' for commands.\n";
std::string input;
while (true) {
std::cout << getPrompt() << " ";
std::getline(std::cin, input);
processCommand(input);
}
}
std::string Terminal::getPrompt() const {
return "terminal";
}
void Terminal::processCommand(const std::string& command) {
std::istringstream iss(command);
std::string cmd;
iss >> cmd;
if (cmd == "help") {
showHelp();
} else if (cmd == "exit") {
std::cout << "Goodbye!\n";
exit(0);
} else if (cmd == "ls") {
currentDir->displayContent();
} else if (cmd == "cd") {
handleCd(iss);
} else if (cmd == "cat") {
handleCat(iss);
} else if (cmd == "touch") {
handleTouch(iss);
} else if (cmd == "mkdir") {
handleMkdir(iss);
} else if (cmd == "rm") {
handleRm(iss);
} else if (cmd == "restore") {
handleRestore(iss);
} else if (cmd == "mv") {
handleMv(iss);
} else if (cmd == "edit") {
handleEdit(iss);
} else {
std::cout << "Unknown command. Type 'help' for available commands.\n";
}
}
void Terminal::showHelp() {
std::cout
<< "Available commands:\n"
<< "  help     - Show this help\n"
<< "  exit     - Exit terminal\n"
<< "  ls       - List directory contents\n"
<< "  cd <dir> - Change directory\n"
<< "  cat <file> - Display file content\n"
<< "  touch <file> - Create file\n"
<< "  mkdir <dir> - Create directory\n"
<< "  rm <entry> - Hide entry\n"
<< "  restore <entry> - Restore hidden entry\n"
<< "  mv <old> <new> - Rename entry\n"
<< "  edit <file> <content> - Edit file\n";
}
void Terminal::handleCd(std::istringstream& iss) {
std::string dirName;
iss >> dirName;
if (dirName.empty()) {
std::cout << "Usage: cd <directory>\n";
return;
}
Entry* entry = currentDir->findChild(dirName);
if (entry) {
Directory* dir = dynamic_cast<Directory*>(entry);
if (dir) {
currentDir = dir;
} else {
std::cout << "Not a directory: " << dirName << "\n";
}
} else {
std::cout << "Directory not found: " << dirName << "\n";
}
}
void Terminal::handleCat(std::istringstream& iss) {
std::string fileName;
iss >> fileName;
Entry* entry = currentDir->findChild(fileName);
if (entry && !entry->isHidden()) {
entry->displayContent();
} else {
std::cout << "File not found or hidden: " << fileName << "\n";
}
}
void Terminal::handleTouch(std::istringstream& iss) {
std::string fileName;
iss >> fileName;
if (!fileName.empty()) {
auto newFile = std::make_unique<SingleLineFile>(fileName);
currentDir->addChild(std::move(newFile));
std::cout << "File created: " << fileName << "\n";
}
}
void Terminal::handleMkdir(std::istringstream& iss) {
std::string dirName;
iss >> dirName;
if (!dirName.empty()) {
auto newDir = std::make_unique<Directory>(dirName);
currentDir->addChild(std::move(newDir));
std::cout << "Directory created: " << dirName << "\n";
} else {
std::cout << "Usage: mkdir <directory_name>\n";
}
}
void Terminal::handleRm(std::istringstream& iss) {
std::string entryName;
iss >> entryName;
if (entryName.empty()) {
std::cout << "Usage: rm <entry_name>\n";
return;
}
Entry* entry = currentDir->findChild(entryName);
if (entry) {
entry->setHidden(true);
auto it = std::find_if(currentDir->getChildren().begin(),
currentDir->getChildren().end(),
[&entryName](const auto& child) {
return child->getDisplayName() == entryName;
});
if (it != currentDir->getChildren().end()) {
hiddenEntries.push_back(std::move(const_cast<std::unique_ptr<Entry>&>(*it)));
currentDir->removeChild(entryName);
std::cout << "Entry hidden: " << entryName << "\n";
}
} else {
std::cout << "Entry not found: " << entryName << "\n";
}
}
void Terminal::handleRestore(std::istringstream& iss) {
std::string entryName;
iss >> entryName;
if (entryName.empty()) {
std::cout << "Usage: restore <entry_name>\n";
return;
}
auto it = std::find_if(hiddenEntries.begin(), hiddenEntries.end(),
[&entryName](const auto& hiddenEntry) {
   return hiddenEntry->getDisplayName() == entryName;
});
if (it != hiddenEntries.end()) {
(*it)->setHidden(false);
currentDir->addChild(std::move(*it));
hiddenEntries.erase(it);
std::cout << "Entry restored: " << entryName << "\n";
} else {
std::cout << "Hidden entry not found: " << entryName << "\n";
}
}
void Terminal::handleMv(std::istringstream& iss) {
std::string oldName, newName;
iss >> oldName >> newName;
if (oldName.empty() || newName.empty()) {
std::cout << "Usage: mv <old_name> <new_name>\n";
return;
}
Entry* entry = currentDir->findChild(oldName);
if (entry) {
entry->setName(newName);
std::cout << "Entry renamed: " << oldName << " -> " << newName << "\n";
} else {
std::cout << "Entry not found: " << oldName << "\n";
}
}
void Terminal::handleEdit(std::istringstream& iss) {
std::string fileName, content;
iss >> fileName;
std::getline(iss >> std::ws, content); // читаем остаток строки как контент
if (fileName.empty() || content.empty()) {
std::cout << "Usage: edit <file_name> <content>\n";
return;
}
Entry* entry = currentDir->findChild(fileName);
if (entry && !entry->isHidden()) {
if (auto* file = dynamic_cast<SingleLineFile*>(entry)) {
file->setContent(content);
std::cout << "File edited: " << fileName << "\n";
} else if (auto* multiFile = dynamic_cast<MultiLineFile*>(entry)) {
multiFile->setContent(content);
std::cout << "File edited: " << fileName << "\n";
} else {
std::cout << "Cannot edit this type of entry\n";
}
} else {
std::cout << "File not found or hidden: " << fileName << "\n";
}
}
