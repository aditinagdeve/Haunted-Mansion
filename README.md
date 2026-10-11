# Secrets of Ravenwood

A C++17 object-oriented horror adventure with an HTML/CSS/JavaScript frontend. The browser communicates with the C++ game engine using HTTP and JSON.

## Requirements
- C++17 compiler (GCC, Clang or recent MSVC)
- CMake 3.16+
- Internet connection during the first CMake configure to fetch `cpp-httplib` and `nlohmann/json`

## Build
Run these commands from the project root:

```bash
cmake -S . -B build
cmake --build build
```

Run the server:
- Linux/macOS: `./build/backend/ravenwood`
- Windows multi-configuration build: `.\build\backend\Release\ravenwood.exe`
- Windows single-configuration build: `.\build\backend\ravenwood.exe`

Open http://localhost:8080 and keep the terminal running.

## Gameplay
1. Enter the Forgotten Library.
2. Collect the Silver Key.
3. Solve the riddle (answer: `book`).
4. Enter the basement and use the Silver Key to defeat the ghost.
5. Collect the Healing Potion if you need it.
6. Enter the Secret Chamber after the prerequisites are complete.
7. Collect the Raven Emblem and return to the Grand Foyer.

The game state is in memory and resets when the server is restarted.

## API
- `GET /api/health` — health check
- `GET /api/state` — current game state
- `POST /api/action` — perform an action

Example request bodies:
```json
{"action":"move","target":"library"}
{"action":"collect"}
{"action":"solve","answer":"book"}
{"action":"fight"}
{"action":"use_potion"}
{"action":"restart"}
```

## Folder guide
- `backend/include/`: C++ class declarations
- `backend/src/`: C++ class implementations
- `backend/main.cpp`: HTTP server and API routes
- `frontend/`: browser UI
- `docs/`: report and class diagram

## Team work division
1. **Frontend:** `frontend/index.html`, `frontend/style.css`, `frontend/script.js`
2. **Player and character:** `Character.h`, `Player.h`, `Player.cpp`
3. **Ghosts, items and puzzles:** `Ghost.*`, `Item.h`, `item.cpp`, `puzzle.h`, `puzzle.cpp`
4. **Rooms and game management:** `Room.*`, `Game.*`
5. **Integration and documentation:** CMake files, `main.cpp`, README, report, class diagram and testing

Agree on class interfaces before merging work. Avoid having multiple members edit the same file at the same time.

## Test checklist
- [ ] CMake configures and builds successfully.
- [ ] `/api/health` returns JSON.
- [ ] The frontend loads from the C++ server.
- [ ] Movement is limited to connected exits.
- [ ] Collected items enter the inventory only once.
- [ ] Puzzle accepts `book` regardless of capitalization.
- [ ] Ghost encounter reduces health when the Silver Key is missing.
- [ ] Secret Chamber stays locked until prerequisites are complete.
- [ ] Potion restores health and is consumed.
- [ ] Emblem plus return to foyer produces victory.
- [ ] Restart restores the initial state.

## Dependencies
- cpp-httplib: https://github.com/yhirose/cpp-httplib
- nlohmann/json: https://github.com/nlohmann/json
