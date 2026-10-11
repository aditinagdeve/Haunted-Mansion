
#pragma once
#include <string>

class Puzzle {
public:
    Puzzle(const std::string& question, const std::string& answer,
           const std::string& hint);

    const std::string& getQuestion() const;
    const std::string& getHint() const;
    bool isSolved() const;
    bool checkAnswer(const std::string& answer);

private:
    std::string question_;
    std::string answer_;
    std::string hint_;
    bool solved_;
};
