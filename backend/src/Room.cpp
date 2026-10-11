#include "../include/Room.h"

Room::Room(int roomId, string roomName, string roomDescription,
           vector<int> roomConnections, string roomItem,
           bool ghost, bool puzzle, string question, string answer) {
    id = roomId;
    name = roomName;
    description = roomDescription;
    connections = roomConnections;
    item = roomItem;
    ghostActive = ghost;
    puzzleActive = puzzle;
    visited = false;
    puzzleQuestion = question;
    puzzleAnswer = answer;
}

int Room::getId() const {
    return id;
}

string Room::getName() const {
    return name;
}

string Room::getDescription() const {
    return description;
}

vector<int> Room::getConnections() const {
    return connections;
}

string Room::getItem() const {
    return item;
}

bool Room::hasGhost() const {
    return ghostActive;
}

bool Room::hasPuzzle() const {
    return puzzleActive;
}

bool Room::isVisited() const {
    return visited;
}

string Room::getPuzzleQuestion() const {
    return puzzleQuestion;
}

string Room::getPuzzleAnswer() const {
    return puzzleAnswer;
}

void Room::setVisited(bool value) {
    visited = value;
}

void Room::removeItem() {
    item = "";
}

void Room::defeatGhost() {
    ghostActive = false;
}

void Room::solvePuzzle() {
    puzzleActive = false;
}
