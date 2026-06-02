#ifndef MULTILINEFILE_H
#define MULTILINEFILE_H

#include "Entry.h"
#include <vector>
#include <string>

class MultiLineFile : public Entry {
private:
    std::vector<std::string> lines;

public:
    MultiLineFile(const std::string& n);
    void displayContent() const override;
    bool edit(const std::string& newContent) override;
    void setContent(const std::string& newContent);
};

#endif
