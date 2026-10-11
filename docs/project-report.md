# Secrets of Ravenwood — Project Report

## 1. Introduction
Secrets of Ravenwood is a single-player horror adventure set in a haunted mansion. The player explores rooms, collects items, solves a riddle, encounters ghosts and attempts to escape.

## 2. Objectives
- Apply object-oriented programming principles in C++.
- Separate the web interface from game rules.
- Demonstrate object interaction and room-based game state.
- Connect a browser frontend to a C++ server using HTTP and JSON.

## 3. Technologies
- C++17 for game logic and backend server.
- HTML5, CSS3 and JavaScript for the frontend.
- CMake for configuring and building the application.
- cpp-httplib for HTTP and nlohmann/json for JSON data.

## 4. System architecture
The browser sends player actions as JSON to the C++ server. The server validates actions, updates the game state and returns the new state. JavaScript renders the response. The backend is authoritative: the frontend cannot directly decide whether a room is unlocked or a puzzle is solved.

## 5. Main classes
- `Character`: abstract base class shared by players and ghosts.
- `Player`: encapsulates health, score and inventory.
- `Ghost`: base ghost class; `LibraryGhost` and `BasementGhost` override virtual behaviour.
- `Item`: represents a collectible object.
- `Puzzle`: stores a question, answer, hint and solved state.
- `Room`: represents a location and owns optional items, ghosts and puzzles.
- `Game`: coordinates the player, rooms, actions and ending conditions.

## 6. OOP concepts demonstrated
- **Encapsulation:** private player inventory and score, exposed through methods.
- **Inheritance:** `Player` and `Ghost` derive from `Character`; specialised ghosts derive from `Ghost`.
- **Polymorphism:** virtual `getType()` and `haunt()` methods are overridden by derived classes.
- **Abstraction:** `Character` defines a common interface; `Game::performAction` provides a high-level action interface.
- **Composition:** `Room` owns optional item, ghost and puzzle objects.
- **STL containers:** vectors and unordered maps store inventory, exits and rooms.
- **Exception handling:** invalid JSON and action processing errors are handled at the API boundary.

## 7. Game rules
Explore the foyer, library and basement. Collect the Silver Key, solve the library riddle, defeat the basement ghost, enter the Secret Chamber and collect the Raven Emblem. Return to the foyer to win. The Healing Potion restores health.

## 8. Testing
Run the game locally and verify the checklist in README.md. Record actual test results after running on the team's computers; do not claim tests passed until verified.

## 9. Limitations and future work
Game state is stored in memory and resets when the server restarts. Future enhancements could include save/load support, more rooms and puzzles, automated unit tests, audio, custom artwork and a persistent database.
