#ifndef DIRECTORY_H
#define DIRECTORY_H
#include "Entry.h"
#include <vector>
#include <memory>
#include <string>
class Directory : public Entry {
  private:
  std::vector<std::unique_ptr<Entry>> children;
  public:
  Directory(const std::string& n);
  Entry* asDirectory() override;
  void displayContent() const override;
  bool edit(const std::string&) override;
  Entry* findChild(const std::string& name);
  void addChild(std::unique_ptr<Entry> child);
  const std::vector<std::unique_ptr<Entry>>& getChildren() const;
  void removeChild(const std::string& entryName);
};
#endif
