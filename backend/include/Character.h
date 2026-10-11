
#ifndef CHARACTER_H
#define CHARACTER_H

#include <string>

class Character {
protected:
    std::string name;
    int health;

public:
    Character(const std::string& characterName, int characterHealth)
        : name(characterName), health(characterHealth) {}

    virtual ~Character() = default;

    std::string getName() const {
        return name;
    }

    int getHealth() const {
        return health;
    }

    void takeDamage(int damage) {
        if (damage <= 0) {
            return;
        }

        health -= damage;

        if (health < 0) {
            health = 0;
        }
    }

    bool isAlive() const {
        return health > 0;
    }
};

#endif
