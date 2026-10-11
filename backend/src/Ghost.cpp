

#include "Ghost.h"

Ghost::Ghost(const std::string& name, int strength, const std::string& description)
    : Character(name, 1), strength_(strength), description_(description), defeated_(false) {}
std::string Ghost::getType() const { return "Ghost"; }
int Ghost::getStrength() const { return strength_; }
const std::string& Ghost::getDescription() const { return description_; }
bool Ghost::isDefeated() const { return defeated_; }
std::string Ghost::haunt() const { return "A cold presence fills the room."; }
void Ghost::defeat() { defeated_ = true; }

LibraryGhost::LibraryGhost()
    : Ghost("The Whisper", 12, "A pale figure flickers between the library shelves.") {}
std::string LibraryGhost::getType() const { return "Library Ghost"; }
std::string LibraryGhost::haunt() const { return "The pages flutter as a whisper circles you."; }

BasementGhost::BasementGhost()
    : Ghost("The Warden", 20, "A spectral keeper guards the flooded basement.") {}
std::string BasementGhost::getType() const { return "Basement Ghost"; }
std::string BasementGhost::haunt() const { return "The Warden rises from the dark water."; }




