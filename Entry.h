#ifndef ENTRY_H
#define ENTRY_H

#include <string>
#include <iostream>
class Directory; 

class Entry {
protected:
    std::string name;
    bool hidden;

public:
    Entry(const std::string& n);
    virtual ~Entry() = default;

    std::string getDisplayName() const;
    bool isHidden() const;
    void setHidden(bool h);
    void setName(const std::string& newName);

    // Полиморфные методы
    virtual void displayContent() const = 0;
    virtual Entry* asDirectory();
    virtual bool edit(const std::string& content) = 0;
};

#endif
