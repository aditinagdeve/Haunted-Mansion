#pragma once
#include "Character.h"
#include <string>

class Ghost : public Character {
public:
    Ghost(const std::string& name, int strength, const std::string& description);
    std::string getType() const override;
    int getStrength() const;
    const std::string& getDescription() const;
    bool isDefeated() const;
    virtual std::string haunt() const;
    void defeat();

private:
    int strength_;
    std::string description_;
    bool defeated_;
};

class LibraryGhost : public Ghost {
public:
    LibraryGhost();
    std::string getType() const override;
    std::string haunt() const override;
};

class BasementGhost : public Ghost {
public:
    BasementGhost();
    std::string getType() const override;
    std::string haunt() const override;
};

