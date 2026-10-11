#include "../include/Game.h"

#include <iostream>
#include <fstream>
#include <algorithm>
#include <cctype>

using namespace std;

Game::Game() {
    setupRooms();
    restartGame();
}

void Game::setupRooms() {
    rooms.clear();

    rooms.emplace_back(
        0, "Entrance Hall",
        "You enter a dark mansion. Dust covers the floor.",
        vector<int>{1}
    );

    rooms.emplace_back(
        1, "Grand Corridor",
        "Old portraits hang on the walls.",
        vector<int>{0, 2, 3}
    );

    rooms.emplace_back(
        2, "Library",
        "Ancient books hide a mysterious riddle.",
        vector<int>{1, 4}, "Old Note",
        false, true,
        "What has keys but cannot open locks?",
        "piano"
    );

    rooms.emplace_back(
        3, "Haunted Kitchen",
        "A ghost blocks your path!",
        vector<int>{1, 4}, "Health Potion",
        true
    );

    rooms.emplace_back(
        4, "Secret Study",
        "You discover a dusty desk and a locked cabinet.",
        vector<int>{2, 3, 5}, "Golden Key"
    );

    rooms.emplace_back(
        5, "Treasure Chamber",
        "You have reached the final chamber.",
        vector<int>{4}, "",
        false, true,
        "Solve this: 2 + 2 = ?",
        "4"
    );
}

void Game::restartGame() {
    currentRoom = 0;
    health = 100;
    hasKey = false;
    gameOver = false;
    won = false;

    for (size_t i = 0; i < rooms.size(); i++) {
        rooms[i].setVisited(false);
    }

    // Reset items, ghosts, and puzzles by rebuilding the rooms.
    setupRooms();

    cout << "\n====================================\n";
    cout << "  THE HAUNTED MANSION: RAVENWOOD\n";
    cout << "====================================\n";
    cout << "Find the Golden Key and escape alive!\n";
}

void Game::showCurrentRoom() {
    Room &room = rooms[currentRoom];

    room.setVisited(true);

    cout << "\n------------------------------------\n";
    cout << "Room: " << room.getName() << "\n";
    cout << room.getDescription() << "\n";
    cout << "Health: " << health << "\n";

    if (hasKey) {
        cout << "Inventory: Golden Key\n";
    } else {
        cout << "Inventory: Empty\n";
    }

    if (room.hasGhost()) {
        cout << "WARNING: A ghost is here!\n";
    }

    if (room.hasPuzzle()) {
        cout << "A puzzle needs to be solved.\n";
    }

    if (!room.getItem().empty()) {
        cout << "Item found: " << room.getItem() << "\n";
    }

    cout << "\nConnected rooms:\n";

    vector<int> exits = room.getConnections();

    for (size_t i = 0; i < exits.size(); i++) {
        cout << exits[i] << " - "
             << rooms[exits[i]].getName() << "\n";
    }
}

void Game::movePlayer() {
    Room &room = rooms[currentRoom];
    vector<int> exits = room.getConnections();

    cout << "\nEnter destination room number: ";

    int destination;
    cin >> destination;

    if (cin.fail()) {
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "Invalid input. Enter a room number.\n";
        return;
    }

    if (find(exits.begin(), exits.end(), destination) == exits.end()) {
        cout << "You cannot move to that room from here.\n";
        return;
    }

    if (destination == 5 && !hasKey) {
        cout << "The Treasure Chamber is locked!\n";
        cout << "Find the Golden Key first.\n";
        return;
    }

    currentRoom = destination;

    cout << "You moved to "
         << rooms[currentRoom].getName() << ".\n";

    checkWin();
}

void Game::exploreRoom() {
    Room &room = rooms[currentRoom];

    // Handle a ghost encounter.
    if (room.hasGhost()) {
        cout << "\nThe ghost attacks you!\n";
        cout << "1. Fight the ghost\n";
        cout << "2. Run away\n";
        cout << "Choose: ";

        int choice;
        cin >> choice;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Invalid choice.\n";
            return;
        }

        if (choice == 1) {
            health -= 25;
            room.defeatGhost();

            cout << "You defeated the ghost, but lost 25 health.\n";
        } else if (choice == 2) {
            cout << "You escaped the encounter. Try another room.\n";
            return;
        } else {
            cout << "Invalid choice.\n";
            return;
        }

        if (health <= 0) {
            health = 0;
            gameOver = true;
            cout << "\nYou ran out of health. Game over!\n";
            return;
        }
    }

    // Handle a puzzle.
    if (room.hasPuzzle()) {
        cout << "\nPUZZLE: "
             << room.getPuzzleQuestion() << "\n";
        cout << "Your answer: ";

        string answer;
        cin >> ws;
        getline(cin, answer);

        transform(answer.begin(), answer.end(),
                  answer.begin(),
                  [](unsigned char c) {
                      return static_cast<char>(tolower(c));
                  });

        string correctAnswer = room.getPuzzleAnswer();

        transform(correctAnswer.begin(), correctAnswer.end(),
                  correctAnswer.begin(),
                  [](unsigned char c) {
                      return static_cast<char>(tolower(c));
                  });

        if (answer == correctAnswer) {
            room.solvePuzzle();
            cout << "Correct! The puzzle is solved.\n";
        } else {
            health -= 10;
            cout << "Wrong answer! You lost 10 health.\n";

            if (health <= 0) {
                health = 0;
                gameOver = true;
                cout << "You ran out of health. Game over!\n";
                return;
            }
        }
    }

    // Collect an item.
    if (!room.getItem().empty()) {
        string itemName = room.getItem();

        cout << "\nDo you want to collect "
             << itemName << "? (y/n): ";

        char choice;
        cin >> choice;

        if (choice == 'y' || choice == 'Y') {
            if (itemName == "Golden Key") {
                hasKey = true;
                cout << "You collected the Golden Key!\n";
            } else if (itemName == "Health Potion") {
                health += 25;

                if (health > 100) {
                    health = 100;
                }

                cout << "You used the Health Potion. Health: "
                     << health << "\n";
            } else {
                cout << "You collected " << itemName << ".\n";
            }

            room.removeItem();
        }
    }

    checkWin();
}

void Game::checkWin() {
    if (currentRoom == 5 &&
        hasKey &&
        !rooms[currentRoom].hasPuzzle()) {

        won = true;
        gameOver = true;

        cout << "\n====================================\n";
        cout << "CONGRATULATIONS!\n";
        cout << "You solved the mystery of Ravenwood!\n";
        cout << "YOU WIN!\n";
        cout << "====================================\n";
    }
}

void Game::saveGame() {
    ofstream file("savegame.txt");

    if (!file) {
        cout << "Unable to save the game.\n";
        return;
    }

    file << currentRoom << "\n";
    file << health << "\n";
    file << hasKey << "\n";

    file.close();

    cout << "Game progress saved to savegame.txt.\n";
}

void Game::loadGame() {
    ifstream file("savegame.txt");

    if (!file) {
        cout << "No saved game found.\n";
        return;
    }

    int savedRoom;
    int savedHealth;
    bool savedKey;

    if (!(file >> savedRoom >> savedHealth >> savedKey)) {
        cout << "Save file is invalid.\n";
        return;
    }

    if (savedRoom < 0 ||
        savedRoom >= static_cast<int>(rooms.size()) ||
        savedHealth < 1 ||
        savedHealth > 100) {

        cout << "Saved data is invalid.\n";
        return;
    }

    currentRoom = savedRoom;
    health = savedHealth;
    hasKey = savedKey;
    gameOver = false;
    won = false;

    rooms[currentRoom].setVisited(true);

    file.close();

    cout << "Game progress loaded successfully.\n";
}

void Game::run() {
    int choice;

    while (true) {
        cout << "\n\n========== MAIN MENU ==========\n";
        cout << "1. New Game\n";
        cout << "2. Continue Saved Game\n";
        cout << "3. Exit\n";
        cout << "Choose: ";

        cin >> choice;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Please enter a valid number.\n";
            continue;
        }

        if (choice == 1) {
            restartGame();
        } else if (choice == 2) {
            loadGame();
        } else if (choice == 3) {
            cout << "Leaving the mansion. Goodbye!\n";
            return;
        } else {
            cout << "Invalid choice.\n";
            continue;
        }

        while (!gameOver) {
            showCurrentRoom();

            cout << "\n========== GAME MENU ==========\n";
            cout << "1. Move to another room\n";
            cout << "2. Explore room\n";
            cout << "3. Save game\n";
            cout << "4. Return to main menu\n";
            cout << "Choose: ";

            cin >> choice;

            if (cin.fail()) {
                cin.clear();
                cin.ignore(10000, '\n');
                cout << "Please enter a valid number.\n";
                continue;
            }

            if (choice == 1) {
                movePlayer();
            } else if (choice == 2) {
                exploreRoom();
            } else if (choice == 3) {
                saveGame();
            } else if (choice == 4) {
                break;
            } else {
                cout << "Invalid choice.\n";
            }
        }

        if (won) {
            cout << "Thanks for playing!\n";
        } else if (health <= 0) {
            cout << "Try again to solve the mansion's mystery.\n";
        }
    }
}
