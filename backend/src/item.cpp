

#include "Item.h"

Item::Item(const std::string& id, const std::string& name,
           const std::string& description, const std::string& kind)
    : id_(id), name_(name), description_(description), kind_(kind) {}

const std::string& Item::getId() const { return id_; }
const std::string& Item::getName() const { return name_; }
const std::string& Item::getDescription() const { return description_; }
const std::string& Item::getKind() const { return kind_; }
