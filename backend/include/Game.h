#ifndef GAME_H
#define GAME_H

#include "Room.h"
#include <vector>
#include <string>

class Game {
private:
    std::vector<Room> rooms;
    int currentRoom;
    int health;
    bool hasKey;
    bool gameOver;
    bool won;

    void setupRooms();
    void showCurrentRoom();
    void movePlayer();
    void exploreRoom();
    void saveGame();
    void loadGame();
    void restartGame();
    void checkWin();

public:
    Game();
    void run();
};

#endif
