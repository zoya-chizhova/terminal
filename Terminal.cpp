#include "Directory.cpp"
#include "SingleLineFile.cpp"
#include "MultiLineFile.cpp"
#include <sstream>
#include <iostream>
#include <memory>

class Terminal {
private:
    std::unique_ptr<Directory> root;
    Directory* currentDir;
    std::vector<std::unique_ptr<Entry>> hiddenEntries;

#Terminal() {
    root = std::make_unique<Directory>("root");
    currentDir = root.get();
}

#void run() {
    std::cout << "Virtual Terminal started. Type 'help' for commands.\n";
    std::string input;

    while (true) {
        std::cout << getPrompt() << " ";
        std::getline(std::cin, input);
        processCommand(input);
    }
}

std::string getPrompt() const {
    // Упрощённая реализация пути
    return "terminal";
}

void processCommand(const std::string& command) {
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

void showHelp() {
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

void handleCd(std::istringstream& iss) {
    std::string dirName;
    iss >> dirName;

    if (dirName.empty()) {
        std::cout << "Usage: cd <directory>\n";
        return;
    }

    Entry* entry = currentDir->findChild(dirName);
    if (entry) {
        Directory* dir = entry->asDirectory();
        if (dir) {
            currentDir = dir;
        } else {
            std::cout << "Not a directory: " << dirName << "\n";
        }
    } else {
        std::cout << "Directory not found: " << dirName << "\n";
    }
}

void handleCat(std::istringstream& iss) {
    std::string fileName;
    iss >> fileName;

    Entry* entry = currentDir->findChild(fileName);
    if (entry && !entry->isHidden()) {
        entry->displayContent();
    } else {
        std::cout << "File not found or hidden: " << fileName << "\n";
    }
}

void handleTouch(std::istringstream& iss) {
    std::string fileName;
    iss >> fileName;

    if (!fileName.empty()) {
        auto newFile = std::make_unique<SingleLineFile>(fileName);
        currentDir->addChild(std::move(newFile));
        std::cout << "File created: " << fileName << "\n";
    }
}

void handleMkdir(std::istringstream& iss) {
    std::string dirName;
    iss >> dirName;

    if (!dirName.empty()) {
        auto newDir = std::make_unique<Directory>(dirName);
        currentDir->addChild(std::move(newDir));
        std::
