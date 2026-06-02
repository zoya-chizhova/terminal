#include "Entry.h"

#include "MultiLineFile.h"
#include <sstream>

MultiLineFile::MultiLineFile(const std::string& n) : Entry(n) {}

void MultiLineFile::displayContent() const {
    for (const auto& line : lines) {
        std::cout << line << "\n";
    }
}

bool MultiLineFile::edit(const std::string& newContent) {
    lines.clear();
    std::istringstream stream(newContent);
    std::string line;
    while (std::getline(stream, line)) {
        lines.push_back(line);
    }
    return true;
}

void MultiLineFile::setContent(const std::string& newContent) {
    edit(newContent); 
}
