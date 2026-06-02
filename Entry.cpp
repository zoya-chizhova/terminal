#include "Entry.h"
#include "Directory.h" 
#include <iostream>

Entry::Entry(const std::string& n) : name(n), hidden(false) {}

std::string Entry::getDisplayName() const {
    return name;
}

bool Entry::isHidden() const {
    return hidden;
}

void Entry::setHidden(bool h) {
    hidden = h;
}

void Entry::setName(const std::string& newName) {
    name = newName;
}

Entry* Entry::asDirectory() {
    return nullptr;
}
