
#ifndef PUZZLE_H
#define PUZZLE_H

#include <string>
using namespace std;

class Puzzle {
private:
    string question;
    string answer;
    bool solved;

public:
    Puzzle(string q, string a);

    string getQuestion() const;
    bool isSolved() const;

    bool solve(string playerAnswer);
};

#endif
