#include "Room.h"
#include <algorithm>

Room::Room(const std::string& id, const std::string& name,
           const std::string& description)
    : id_(id), name_(name), description_(description) {}

const std::string& Room::getId() const { return id_; }
const std::string& Room::getName() const { return name_; }
const std::string& Room::getDescription() const { return description_; }
const std::vector<std::string>& Room::getExits() const { return exits_; }

void Room::addExit(const std::string& roomId) {
    if (std::find(exits_.begin(), exits_.end(), roomId) == exits_.end())
        exits_.push_back(roomId);
}
void Room::setItem(const Item& item) { item_ = std::make_unique<Item>(item); }
const Item* Room::getItem() const { return item_.get(); }
bool Room::hasItem() const { return static_cast<bool>(item_); }
void Room::removeItem() { item_.reset(); }
void Room::setGhost(std::unique_ptr<Ghost> ghost) { ghost_ = std::move(ghost); }
Ghost* Room::getGhost() const { return ghost_.get(); }
void Room::setPuzzle(std::unique_ptr<Puzzle> puzzle) { puzzle_ = std::move(puzzle); }
Puzzle* Room::getPuzzle() const { return puzzle_.get(); }
