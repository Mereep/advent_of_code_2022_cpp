//
// Created by Richard Vogel on 02.12.22.
//

#include "day2.h"
#include <string>
#include <iostream>
#include <map>

using namespace std;


// every game situation has some defined points (worth)
std::map<string, uint> GAME_TO_POINTS = {
        {"AX", 3}, // Rock -> Rock == Tie
        {"AY", 6}, // Rock -> Paper == Win
        {"AZ", 0}, // Rock -> Scissors = Loose
        {"BX", 0},
        {"BY", 3},
        {"BZ", 6},
        {"CX", 6},
        {"CY", 0},
        {"CZ", 3},

};

// Every move has defined points (worth)
std::map<char, uint> SELECTION_TO_POINTS = {
        {'X', 1},
        {'Y', 2},
        {'Z', 3},
};


// task 2 selects a move by the wish to win / loose or tie given the other players move
std::map<string, char> SELECTIONS = {
        {"AX", 'Z'},
        {"AY", 'X'},
        {"AZ", 'Y'},
        {"BX", 'X'},
        {"BY", 'Y'},
        {"BZ", 'Z'},
        {"CX", 'Y'},
        {"CY", 'Z'},
        {"CZ", 'X'},
};

Day2::Day2(const std::vector<std::string>& lines) : Day(lines) {}

std::string Day2::part1() {
    uint total = 0;
    for (auto line : lines) {
        // read the single letters e.g., `A X`
        char l = line[0];
        char r = line[2];

        // Build board situation e.g., `AX`
        string board = string(1, l) + string(1, r);

        // calculate the points
        uint points = GAME_TO_POINTS.at(board);
        points += SELECTION_TO_POINTS.at(r);
        total += points;
    }
    return to_string(total);

}

std::string Day2::part2() {
    uint total = 0;
    for (auto line : lines) {
        // as part 1
        char l = line[0];
        char r = line[2];
        string board = string(1, l) + string(1, r);

        // select the correct move (X == loose, Y == Draw, Z == Win)
        char selection = SELECTIONS.at(board);

        // substitute the move
        string boardNew = "" + board;
        boardNew[1] = selection;


        // calculate points as before
        uint points = GAME_TO_POINTS.at(boardNew);
        points += SELECTION_TO_POINTS.at(selection);
        total += points;
    }

    return to_string(total);}
