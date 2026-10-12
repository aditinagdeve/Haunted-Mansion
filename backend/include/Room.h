#pragma once
#include "Ghost.h"
#include "Item.h"
#include "puzzle.h"
#include <memory>
#include <string>
#include <vector>

class Room {
public:
    Room(const std::string& id, const std::string& name,
         const std::string& description);

    const std::string& getId() const;
    const std::string& getName() const;
    const std::string& getDescription() const;
    const std::vector<std::string>& getExits() const;

    void addExit(const std::string& roomId);
    void setItem(const Item& item);
    const Item* getItem() const;
    bool hasItem() const;
    void removeItem();

    void setGhost(std::unique_ptr<Ghost> ghost);
    Ghost* getGhost() const;
    void setPuzzle(std::unique_ptr<Puzzle> puzzle);
    Puzzle* getPuzzle() const;

private:
    std::string id_;
    std::string name_;
    std::string description_;
    std::vector<std::string> exits_;
    std::unique_ptr<Item> item_;
    std::unique_ptr<Ghost> ghost_;
    std::unique_ptr<Puzzle> puzzle_;
};
