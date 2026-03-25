#include "Entry.cpp"

class MultiLineFile : public Entry {
private:
    std::vector<std::string> lines;

#MultiLineFile(const std::string& n) : Entry(n) {}

# void displayContent() const override {
    for (const auto& line : lines) {
        std::cout << line << "\n";
    }
}

# bool edit(const std::string& newContent) override {
    lines.clear();
    lines.push_back(newContent);
    return true;
}
};
