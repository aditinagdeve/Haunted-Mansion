

    #pragma once
#include <string>

class Item {
public:
    Item(const std::string& id, const std::string& name,
         const std::string& description, const std::string& kind);

    const std::string& getId() const;
    const std::string& getName() const;
    const std::string& getDescription() const;
    const std::string& getKind() const;

private:
    std::string id_;
    std::string name_;
    std::string description_;
    std::string kind_;
};
