//
// Created by Richard Vogel on 06.12.22.
//
#include <iostream>
#include <map>
#include "day6.h"
#include <set>

using namespace std;

Day6::Day6(const std::vector<std::string> &lines): Day(lines) {}

/***
 * Finds the occurrence of the first subsequence of chars which are all unique and have a length of `n_unique_chars`.
 *
 * @param message
 * @param n_unique_chars
 * @return the char position AFTER the occurence
 */
uint findMessageStart(const string& message, const uint n_unique_chars) {
    for (uint i = 0; i < message.size() - n_unique_chars; i++) {
        set<char> basket;

        // get the next n_unique_chars characters
        for (int j = 0; j < n_unique_chars; j++) {
            basket.insert(message[i + j]);
        }

        // check if they are all unique
        if (basket.size() == n_unique_chars) {
            // return the next character number after the unique sequence
            return i + n_unique_chars;
        }
    }

    // maximum uint
    return -1;
}

std::string Day6::part1() {
    return to_string(findMessageStart(lines[0], 4));
}


std::string Day6::part2() {
    return to_string(findMessageStart(lines[0], 14));
}
