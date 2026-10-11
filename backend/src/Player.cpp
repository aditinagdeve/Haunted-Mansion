#include "Player.h"
#include <algorithm>

Player::Player(const std::string& name)
    : Character(name.empty() ? "Explorer" : name, 100), score_(0) {}

std::string Player::getType() const { return "Player"; }
int Player::getScore() const { return score_; }
const std::vector<std::string>& Player::getInventory() const { return inventory_; }

void Player::takeDamage(int amount) {
    if (amount > 0) setHealth(std::max(0, health_ - amount));
}
void Player::heal(int amount) {
    if (amount > 0 && isAlive()) setHealth(std::min(100, health_ + amount));
}
void Player::addScore(int amount) {
    if (amount > 0) score_ += amount;
}
bool Player::addItem(const std::string& itemName) {
    if (itemName.empty() || hasItem(itemName)) return false;
    inventory_.push_back(itemName);
    return true;
}
bool Player::hasItem(const std::string& itemName) const {
    return std::find(inventory_.begin(), inventory_.end(), itemName) != inventory_.end();
}
bool Player::removeItem(const std::string& itemName) {
    auto it = std::find(inventory_.begin(), inventory_.end(), itemName);
    if (it == inventory_.end()) return false;
    inventory_.erase(it);
    return true;
}
void Player::reset() {
    setHealth(100);
    score_ = 0;
    inventory_.clear();
}
