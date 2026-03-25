#include "Entry.cpp"
#include <vector>
#include <memory>
#include <algorithm>

class Directory : public Entry {
private:
    std::vector<std::unique_ptr<Entry>> children;

publicDirectory(const std::string& n) : Entry(n) {}

# Entry* asDirectory() override {
    return this;
}

# void displayContent() const override {
    for (const auto& child : children) {
        if (!child->isHidden()) {
            std::cout << child->getDisplayName() << "\n";
        }
    }
}

# bool edit(const std::string&) override {
    std::cout << "Cannot edit directory\n";
    return false;
}

Entry* findChild(const std::string& name) {
    auto it = std::find_if(children.begin(), children.end(),
        [&name](const std::unique_ptr<Entry>& e) {
            return e->getDisplayName() == name;
        });
    return (it != children.end()) ? it->get() : nullptr;
}

void addChild(std::unique_ptr<Entry> child) {
    children.push_back(std::move(child));
}
};
