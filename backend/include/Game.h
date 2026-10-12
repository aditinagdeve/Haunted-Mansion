#pragma once
#include "Player.h"
#include "Room.h"
#include <nlohmann/json.hpp>
#include <memory>
#include <string>
#include <unordered_map>

class Game {
public:
    Game();
    nlohmann::json getState() const;
    nlohmann::json performAction(const nlohmann::json& request);

private:
    Player player_;
    std::unordered_map<std::string, std::unique_ptr<Room>> rooms_;
    std::string currentRoomId_;
    std::string message_;
    bool puzzleSolved_;
    bool basementGhostDefeated_;
    bool won_;
    bool lost_;

    void buildWorld();
    Room* currentRoom();
    const Room* currentRoom() const;
    void updateEndState();
    void setMessage(const std::string& message);
};
