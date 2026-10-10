
#ifndef ITEM_H
#define ITEM_H

#include <string>

enum class ItemType {
    Key,
    Potion,
    Clue,
    SoulSeal,
    Lantern
};

class Item {
private:
    std::string name;
    std::string description;
    ItemType type;

public:
    Item(const std::string& name,
         const std::string& description,
         ItemType type);

    std::string getName() const;
    std::string getDescription() const;
    ItemType getType() const;

    void display() const;
};

#endif
