#include "Player.h"
#include <iostream>
#include <algorithm>

using namespace std;

Player::Player(string playerName)
{
    name = playerName;
    health = 100;
    score = 0;
}

string Player::getName() const
{
    return name;
}

int Player::getHealth() const
{
    return health;
}

int Player::getScore() const
{
    return score;
}

void Player::takeDamage(int damage)
{
    if (damage < 0)
        return;

    health -= damage;

    if (health < 0)
        health = 0;

    cout << name << " took " << damage
         << " damage!" << endl;

    cout << "Current health: "
         << health << endl;
}

void Player::addScore(int points)
{
    score += points;

    if (score < 0)
        score = 0;
}

void Player::collectItem(const string& item)
{
    inventory.push_back(item);

    cout << name << " collected: "
         << item << endl;
}

void Player::displayInventory() const
{
    cout << "\n--- Player Inventory ---\n";

    if (inventory.empty())
    {
        cout << "Inventory is empty.\n";
        return;
    }

    for (const string& item : inventory)
    {
        cout << "- " << item << endl;
    }
}

bool Player::hasItem(const string& item) const
{
    return find(inventory.begin(),
                inventory.end(),
                item) != inventory.end();
}

int Player::countItems(const string& item) const
{
    return count(inventory.begin(),
                 inventory.end(),
                 item);
}
