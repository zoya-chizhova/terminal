#ifndef SINGLELINEFILE_H
#define SINGLELINEFILE_H

#include "Entry.h"
#include <string>

class SingleLineFile : public Entry {
private:
    std::string content;

public:
    SingleLineFile(const std::string& n, const std::string& c = "");
    void displayContent() const override;
    bool edit(const std::string& newContent) override;
    void setContent(const std::string& newContent);
};

#endif
