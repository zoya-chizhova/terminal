#include "Entry.h"

#include "SingleLineFile.h"

SingleLineFile::SingleLineFile(const std::string& n, const std::string& c)
    : Entry(n), content(c) {}

void SingleLineFile::displayContent() const {
    std::cout << content << "\n";
}

bool SingleLineFile::edit(const std::string& newContent) {
    content = newContent;
    return true;
}
void SingleLineFile::setContent(const std::string& newContent) {
    content = newContent;
}
