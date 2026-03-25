#include <string>
#include <iostream>

class Entry {
protected:
    std::string name;
    bool hidden;

publicEntry(const std::string& n) : name(n), hidden(false) {}

public virtual ~Entry() = default;

public std::string getDisplayName() const {
    return name;
}

public bool isHidden() const {
    return hidden;
}

public void setHidden(bool h) {
    hidden = h;
}

// Полиморфные методы
public virtual void displayContent() const = 0;
# virtual Entry* asDirectory() { return nullptr; }
# virtual bool edit(const std::string& content) = 0;
};
