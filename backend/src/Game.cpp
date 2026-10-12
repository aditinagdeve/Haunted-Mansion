#include "Game.h"
#include "Ghost.h"
#include "Item.h"
#include "puzzle.h"
#include <algorithm>
#include <cctype>
#include <exception>

using nlohmann::json;

namespace {
std::string lowerTrim(std::string value) {
    auto notSpace = [](unsigned char c) { return !std::isspace(c); };
    value.erase(value.begin(), std::find_if(value.begin(), value.end(), notSpace));
    value.erase(std::find_if(value.rbegin(), value.rend(), notSpace).base(), value.end());
    std::transform(value.begin(), value.end(), value.begin(),
                   [](unsigned char c) { return static_cast<char>(std::tolower(c)); });
    return value;
}
}

Game::Game()
    : player_("Explorer"), currentRoomId_("foyer"),
      message_("You wake in Ravenwood Manor. Find a way out."),
      puzzleSolved_(false), basementGhostDefeated_(false), won_(false), lost_(false) {
    buildWorld();
}

void Game::buildWorld() {
    rooms_.clear();
    auto foyer = std::make_unique<Room>("foyer", "Grand Foyer",
        "Dust hangs beneath a cracked chandelier. Two dark passages lead deeper into the manor.");
    auto library = std::make_unique<Room>("library", "Forgotten Library",
        "Towering shelves lean over a desk. A riddle is scratched into the wood.");
    auto basement = std::make_unique<Room>("basement", "Flooded Basement",
        "Cold water covers the stone floor. Something watches from the darkness.");
    auto secret = std::make_unique<Room>("secret", "Secret Chamber",
        "A sealed chamber glows with blue light. The manor's final secret lies here.");

    foyer->addExit("library");
    foyer->addExit("basement");
    library->addExit("foyer");
    library->addExit("secret");
    basement->addExit("foyer");
    basement->addExit("secret");
    secret->addExit("library");
    secret->addExit("basement");

    library->setItem(Item("silver-key", "Silver Key",
        "A cold key engraved with a raven.", "key"));
    library->setGhost(std::make_unique<LibraryGhost>());
    library->setPuzzle(std::make_unique<Puzzle>(
        "I have pages but I am not a tree. I hold stories but cannot speak. What am I?",
        "book", "Hint: you can find many of them on these shelves."));
    basement->setItem(Item("health-potion", "Healing Potion",
        "A small vial that restores health.", "potion"));
    basement->setGhost(std::make_unique<BasementGhost>());
    secret->setItem(Item("raven-emblem", "Raven Emblem",
        "The manor's final seal.", "quest"));

    rooms_["foyer"] = std::move(foyer);
    rooms_["library"] = std::move(library);
    rooms_["basement"] = std::move(basement);
    rooms_["secret"] = std::move(secret);
}

Room* Game::currentRoom() { return rooms_.at(currentRoomId_).get(); }
const Room* Game::currentRoom() const { return rooms_.at(currentRoomId_).get(); }
void Game::setMessage(const std::string& message) { message_ = message; }

void Game::updateEndState() {
    if (!player_.isAlive()) {
        lost_ = true;
        won_ = false;
        message_ = "Your strength fades. Ravenwood keeps its secrets. Restart to try again.";
    }
    if (player_.hasItem("Raven Emblem") && currentRoomId_ == "foyer" && player_.isAlive()) {
        won_ = true;
        lost_ = false;
        message_ = "You recovered the Raven Emblem and escaped Ravenwood Manor!";
    }
}

json Game::getState() const {
    const Room* room = currentRoom();
    json exits = json::array();
    for (const auto& exitId : room->getExits()) {
        const auto found = rooms_.find(exitId);
        if (found != rooms_.end())
            exits.push_back({{"id", exitId}, {"name", found->second->getName()}});
    }

    json inventory = json::array();
    for (const auto& item : player_.getInventory()) inventory.push_back(item);

    json item = nullptr;
    if (room->hasItem()) {
        const Item* found = room->getItem();
        item = {{"id", found->getId()}, {"name", found->getName()},
                {"description", found->getDescription()}, {"kind", found->getKind()}};
    }

    json ghost = nullptr;
    const Ghost* roomGhost = room->getGhost();
    if (roomGhost && !roomGhost->isDefeated()) {
        ghost = {{"name", roomGhost->getName()}, {"description", roomGhost->getDescription()},
                 {"strength", roomGhost->getStrength()}, {"type", roomGhost->getType()},
                 {"haunt", roomGhost->haunt()}};
    }

    json puzzle = nullptr;
    const Puzzle* roomPuzzle = room->getPuzzle();
    if (roomPuzzle && !roomPuzzle->isSolved())
        puzzle = {{"question", roomPuzzle->getQuestion()}, {"hint", roomPuzzle->getHint()}};

    return {
        {"player", {{"name", player_.getName()}, {"health", player_.getHealth()},
                    {"score", player_.getScore()}, {"inventory", inventory}}},
        {"room", {{"id", room->getId()}, {"name", room->getName()},
                  {"description", room->getDescription()}, {"exits", exits},
                  {"item", item}, {"ghost", ghost}, {"puzzle", puzzle}}},
        {"message", message_},
        {"status", won_ ? "won" : (lost_ ? "lost" : "playing")},
        {"flags", {{"puzzleSolved", puzzleSolved_},
                   {"basementGhostDefeated", basementGhostDefeated_}}}
    };
}

json Game::performAction(const json& request) {
    if (!request.is_object() || !request.contains("action") || !request["action"].is_string()) {
        setMessage("Invalid action request.");
        return getState();
    }

    const std::string action = request["action"].get<std::string>();
    if ((won_ || lost_) && action != "restart") {
        setMessage("The game has ended. Choose Restart to play again.");
        return getState();
    }

    try {
        if (action == "move") {
            if (!request.contains("target") || !request["target"].is_string()) {
                setMessage("Choose a valid destination.");
            } else {
                const std::string target = request["target"].get<std::string>();
                const auto& exits = currentRoom()->getExits();
                if (std::find(exits.begin(), exits.end(), target) == exits.end()) {
                    setMessage("That passage is not connected to this room.");
                } else if (target == "secret" &&
                           (!player_.hasItem("Silver Key") || !puzzleSolved_ || !basementGhostDefeated_)) {
                    setMessage("The Secret Chamber is sealed. Find the Silver Key, solve the library riddle, and defeat the basement ghost.");
                } else {
                    currentRoomId_ = target;
                    setMessage("You enter " + currentRoom()->getName() + ".");
                    updateEndState();
                }
            }
        } else if (action == "collect") {
            Room* room = currentRoom();
            if (!room->hasItem()) {
                setMessage("There is nothing here to collect.");
            } else {
                const Item* item = room->getItem();
                const std::string name = item->getName();
                const std::string kind = item->getKind();
                if (player_.addItem(name)) {
                    player_.addScore(kind == "quest" ? 50 : 10);
                    room->removeItem();
                    setMessage("Collected: " + name + ".");
                } else setMessage("You already have that item.");
            }
        } else if (action == "fight") {
            Ghost* ghost = currentRoom()->getGhost();
            if (!ghost || ghost->isDefeated()) {
                setMessage("There is no ghost to confront here.");
            } else if (player_.hasItem("Silver Key")) {
                ghost->defeat();
                player_.addScore(25);
                if (currentRoomId_ == "basement") basementGhostDefeated_ = true;
                setMessage(ghost->getName() + " recoils from the Silver Key and dissolves into mist!");
            } else {
                player_.takeDamage(ghost->getStrength());
                setMessage(ghost->haunt() + " You lose " + std::to_string(ghost->getStrength()) +
                           " health. Find the Silver Key before confronting it again.");
            }
        } else if (action == "solve") {
            if (!request.contains("answer") || !request["answer"].is_string()) {
                setMessage("Enter an answer to the riddle.");
            } else {
                Puzzle* puzzle = currentRoom()->getPuzzle();
                if (!puzzle) setMessage("There is no puzzle in this room.");
                else if (puzzle->checkAnswer(request["answer"].get<std::string>())) {
                    puzzleSolved_ = true;
                    player_.addScore(30);
                    setMessage("Correct! The shelves shift, revealing a hidden passage.");
                } else setMessage("That answer is not correct. Try again or ask for a hint.");
            }
        } else if (action == "hint") {
            Puzzle* puzzle = currentRoom()->getPuzzle();
            setMessage(puzzle && !puzzle->isSolved()
                ? puzzle->getHint() : "There is no unsolved puzzle here.");
        } else if (action == "use_potion") {
            if (player_.removeItem("Healing Potion")) {
                player_.heal(35);
                setMessage("The potion restores your strength.");
            } else setMessage("You do not have a Healing Potion.");
        } else if (action == "restart") {
            player_.reset();
            currentRoomId_ = "foyer";
            puzzleSolved_ = false;
            basementGhostDefeated_ = false;
            won_ = false;
            lost_ = false;
            buildWorld();
            setMessage("A new attempt begins. Explore carefully.");
        } else {
            setMessage("Unknown action.");
        }
    } catch (const std::exception&) {
        setMessage("The game could not process that action.");
    }

    updateEndState();
    return getState();
}

    
