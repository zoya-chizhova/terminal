#include "Entry.h"
#include "Directory.h"
#include <algorithm>
Directory::Directory(const std::string& n) : Entry(n) {}
Entry* Directory::asDirectory() {
return this;
}
void Directory::displayContent() const {
for (const auto& child : children) {
if (!child->isHidden()) {
std::cout << child->getDisplayName() << "\n";
}
}
}
bool Directory::edit(const std::string&) {
std::cout << "Cannot edit directory\n";
return false;
}
Entry* Directory::findChild(const std::string& name) {
auto it = std::find_if(children.begin(), children.end(),
[&name](const std::unique_ptr<Entry>& e) {
return e->getDisplayName() == name;
});
return (it != children.end()) ? it->get() : nullptr;
}
void Directory::addChild(std::unique_ptr<Entry> child) {
children.push_back(std::move(child));
}
const std::vector<std::unique_ptr<Entry>>& Directory::getChildren() const {
return children;
}
void Directory::removeChild(const std::string& entryName) {
auto it = std::find_if(children.begin(), children.end(),
[&entryName](const std::unique_ptr<Entry>& e) {
return e->getDisplayName() == entryName;
});
if (it != children.end()) {
children.erase(it);
} else {
std::cout << "Entry not found: " << entryName << "\n";
}
}
