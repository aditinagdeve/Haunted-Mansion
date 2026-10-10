

#include "Item.h"
#include <iostream>

Item::Item(const std::string& name,
           const std::string& description,
           ItemType type)
    : name(name), description(description), type(type) {}

std::string Item::getName() const {
    return name;
}

std::string Item::getDescription() const {
    return description;
}

ItemType Item::getType() const {
    return type;
}

void Item::display() const {
    std::cout << name << ": " << description << '\n';
}
