#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include <vector>

using namespace std;

class Player
{
private:
    string name;
    int health;
    int score;
    vector<string> inventory;

public:
    Player(string playerName);

    string getName() const;
    int getHealth() const;
    int getScore() const;

    void takeDamage(int damage);
    void addScore(int points);

    void collectItem(const string& item);
    void displayInventory() const;

    bool hasItem(const string& item) const;
    int countItems(const string& item) const;
};

#endif
