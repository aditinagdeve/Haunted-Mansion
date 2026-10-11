
#ifndef ROOM_H
#define ROOM_H

#include <string>
#include <vector>

class Room {
private:
    int id;
    std::string name;
    std::string description;
    std::vector<int> connections;
    std::string item;
    bool ghostActive;
    bool puzzleActive;
    bool visited;
    std::string puzzleQuestion;
    std::string puzzleAnswer;

public:
    Room(int roomId, std::string roomName,
         std::string roomDescription,
         std::vector<int> roomConnections,
         std::string roomItem = "",
         bool ghost = false,
         bool puzzle = false,
         std::string question = "",
         std::string answer = "");

    int getId() const;
    std::string getName() const;
    std::string getDescription() const;
    std::vector<int> getConnections() const;
    std::string getItem() const;

    bool hasGhost() const;
    bool hasPuzzle() const;
    bool isVisited() const;

    std::string getPuzzleQuestion() const;
    std::string getPuzzleAnswer() const;

    void setVisited(bool value);
    void removeItem();
    void defeatGhost();
    void solvePuzzle();
};

#endif

