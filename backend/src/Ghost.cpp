
#include "Ghost.h"

Ghost::Ghost(const std::string& name, int damage)
    : name(name), damage(damage) {}

Ghost::~Ghost() = default;

std::string Ghost::getName() const {
    return name;
}

int Ghost::getDamage() const {
    return damage;
}

LibraryGhost::LibraryGhost()
    : Ghost("Library Ghost", 10) {}

std::string LibraryGhost::encounterMessage() const {
    return "A ghost appears between the dusty books!";
}

std::string LibraryGhost::attackMessage() const {
    return "The Library Ghost attacks with flying books!";
}

WardenGhost::WardenGhost()
    : Ghost("Warden Ghost", 20) {}

std::string WardenGhost::encounterMessage() const {
    return "The Basement Warden blocks your path!";
}

std::string WardenGhost::attackMessage() const {
    return "The Warden Ghost strikes with dark energy!";
}

GuardianSpirit::GuardianSpirit()
    : Ghost("Guardian Spirit", 15) {}

std::string GuardianSpirit::encounterMessage() const {
    return "The Guardian Spirit protects the final chamber!";
}

std::string GuardianSpirit::attackMessage() const {
    return "The Guardian Spirit releases a magical blast!";
}
