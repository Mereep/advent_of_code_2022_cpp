//
// Created by Richard Vogel on 02.12.22.
//

#include "day1.h"
#include <string>
#include <iostream>


/**
 * given a list of number strings as
 *
 * ```
 * 11
 * 12
 *
 * 22
 * 33
 * ```
 * will return a vector of sums of the groups (here: 23 and 55)
 * @param lines
 * @return vector of group sums
 */
std::vector<uint64_t> count(const std::vector<std::string>& lines) {
    std::vector<uint64_t> sums;
    uint64_t currSum = 0;

    for(const std::string& line : lines) {
        if (line.empty()) {
            sums.push_back(currSum);
            currSum = 0;
        } else {
            currSum += std::stoi(line);
        }
    }

    return sums;
}

Day1::Day1(const std::vector<std::string>& lines) : Day(lines) {}

// implement part1 and part2 here
std::string Day1::part1() {
    std::vector<uint64_t> sums = count(this->lines);
    auto max = *std::max_element(sums.begin(), sums.end());

    return std::to_string(max);
}

std::string Day1::part2() {
    std::vector<uint64_t> sums = count(this->lines);
    std::sort(sums.begin(), sums.end());
    std::reverse(sums.begin(), sums.end());

    return std::to_string(sums.at(0) + sums.at(1) + sums.at(2));
}
