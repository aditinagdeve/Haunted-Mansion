
#include "Puzzle.h"

Puzzle::Puzzle(string q, string a)
    : question(q), answer(a), solved(false) {
}

string Puzzle::getQuestion() const {
    return question;
}

bool Puzzle::isSolved() const {
    return solved;
}

bool Puzzle::solve(string playerAnswer) {
    if (solved) {
        return true;
    }

    if (playerAnswer == answer) {
        solved = true;
        return true;
    }

    return false;
}
