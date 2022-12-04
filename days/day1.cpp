//
// Created by Richard Vogel on 02.12.22.
//

#include "day1.h"
#include <string>
using namespace std;

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
vector<uint64_t> count(const vector<string>& lines) {
    vector<uint64_t> sums;
    uint64_t currSum = 0;

    for(const string& line : lines) {
        if (line.empty()) {
            sums.push_back(currSum);
            currSum = 0;
        } else {
            currSum += stoi(line);
        }
    }

    return sums;
}

Day1::Day1(const vector<string>& lines) : Day(lines) {}

// implement part1 and part2 here
string Day1::part1() {
    vector<uint64_t> sums = count(this->lines);
    auto max = *max_element(sums.begin(), sums.end());

    return to_string(max);
}

string Day1::part2() {
    vector<uint64_t> sums = count(this->lines);
    sort(sums.begin(), sums.end());
    reverse(sums.begin(), sums.end());

    return to_string(sums.at(0) + sums.at(1) + sums.at(2));
}
