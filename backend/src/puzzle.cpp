
#include "puzzle.h"
#include <algorithm>
#include <cctype>

namespace {
std::string normalize(std::string text) {
    auto notSpace = [](unsigned char c) { return !std::isspace(c); };
    text.erase(text.begin(), std::find_if(text.begin(), text.end(), notSpace));
    text.erase(std::find_if(text.rbegin(), text.rend(), notSpace).base(), text.end());
    std::transform(text.begin(), text.end(), text.begin(),
                   [](unsigned char c) { return static_cast<char>(std::tolower(c)); });
    return text;
}
}

Puzzle::Puzzle(const std::string& question, const std::string& answer,
               const std::string& hint)
    : question_(question), answer_(normalize(answer)), hint_(hint), solved_(false) {}

const std::string& Puzzle::getQuestion() const { return question_; }
const std::string& Puzzle::getHint() const { return hint_; }
bool Puzzle::isSolved() const { return solved_; }

bool Puzzle::checkAnswer(const std::string& answer) {
    if (normalize(answer) == answer_) solved_ = true;
    return solved_;
}
