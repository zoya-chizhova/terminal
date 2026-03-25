#include "Entry.cpp"

class SingleLineFile : public Entry {
private:
    std::string content;

#SingleLineFile(const std::string& n, const std::string& c = "")
    : Entry(n), content(c) {}

# void displayContent() const override {
    std::cout << content << "\n";
}

# bool edit(const std::string& newContent) override {
    content = newContent;
    return true;
}
};
