#include "../include/Player.h"

#include <algorithm>
#include <iostream>
#include <utility>

Player::Player(std::string playerName)
    : Character(std::move(playerName), 100), score(0) {}

int Player::getScore() const {
    return score;
}

void Player::takeDamage(int damage) {
    if (damage <= 0) {
        return;
    }

    Character::takeDamage(damage);

    std::cout << name << " took " << damage << " damage!\n";
    std::cout << "Current health: " << health << '\n';
}

void Player::addScore(int points) {
    score += points;

    if (score < 0) {
        score = 0;
    }
}

void Player::collectItem(const std::string& item) {
    inventory.push_back(item);
    std::cout << name << " collected: " << item << '\n';
}

void Player::displayInventory() const {
    std::cout << "\n--- Player Inventory ---\n";

    if (inventory.empty()) {
        std::cout << "Inventory is empty.\n";
        return;
    }

    for (const std::string& item : inventory) {
        std::cout << "- " << item << '\n';
    }
}

bool Player::hasItem(const std::string& item) const {
    return std::find(inventory.begin(), inventory.end(), item)
           != inventory.end();
}

int Player::countItems(const std::string& item) const {
    return static_cast<int>(
        std::count(inventory.begin(), inventory.end(), item)
    );
}
