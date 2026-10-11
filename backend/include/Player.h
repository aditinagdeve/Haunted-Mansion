#pragma once
#include "Character.h"
#include <string>
#include <vector>

class Player : public Character {
public:
    explicit Player(const std::string& name = "Explorer");

    std::string getType() const override;
    int getScore() const;
    const std::vector<std::string>& getInventory() const;

    void takeDamage(int amount);
    void heal(int amount);
    void addScore(int amount);
    bool addItem(const std::string& itemName);
    bool hasItem(const std::string& itemName) const;
    bool removeItem(const std::string& itemName);
    void reset();

private:
    int score_;
    std::vector<std::string> inventory_;
};
