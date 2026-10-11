#ifndef PLAYER_H
#define PLAYER_H

#include "Character.h"
#include <string>
#include <vector>

class Player : public Character {
private:
    int score;
    std::vector<std::string> inventory;

public:
    explicit Player(std::string playerName);

    int getScore() const;

    void takeDamage(int damage);
    void addScore(int points);

    void collectItem(const std::string& item);
    void displayInventory() const;

    bool hasItem(const std::string& item) const;
    int countItems(const std::string& item) const;
};

#endif
