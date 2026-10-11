#ifndef ROOM_H
#define ROOM_H

#include <string>
#include <vector>
using namespace std;

class Room {
private:
    int id;
    string name;
    string description;
    vector<int> connections;
    string item;
    bool ghostActive;
    bool puzzleActive;
    bool visited;
    string puzzleQuestion;
    string puzzleAnswer;

public:
    Room(int roomId, string roomName, string roomDescription,
         vector<int> roomConnections, string roomItem = "",
         bool ghost = false, bool puzzle = false,
         string question = "", string answer = "");

    int getId() const;
    string getName() const;
    string getDescription() const;
    vector<int> getConnections() const;
    string getItem() const;
    bool hasGhost() const;
    bool hasPuzzle() const;
    bool isVisited() const;
    string getPuzzleQuestion() const;
    string getPuzzleAnswer() const;

    void setVisited(bool value);
    void removeItem();
    void defeatGhost();
    void solvePuzzle();
};

#endif
