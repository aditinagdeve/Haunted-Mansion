
#ifndef GHOST_H
#define GHOST_H

#include <string>

class Ghost {
protected:
    std::string name;
    int damage;

public:
    Ghost(const std::string& name, int damage);
    virtual ~Ghost();

    std::string getName() const;
    int getDamage() const;

    virtual std::string encounterMessage() const = 0;
    virtual std::string attackMessage() const = 0;
};

class LibraryGhost : public Ghost {
public:
    LibraryGhost();
    std::string encounterMessage() const override;
    std::string attackMessage() const override;
};

class WardenGhost : public Ghost {
public:
    WardenGhost();
    std::string encounterMessage() const override;
    std::string attackMessage() const override;
};

class GuardianSpirit : public Ghost {
public:
    GuardianSpirit();
    std::string encounterMessage() const override;
    std::string attackMessage() const override;
};

#endif
