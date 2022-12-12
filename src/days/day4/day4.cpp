//
// Created by Richard Vogel on 04.12.22.
//

#include <string>
#include <iostream>
#include <map>
#include "day4.hpp"

using namespace std;

Day4::Day4(const std::vector<std::string> &lines): Day(lines) {}

// splits on `-` character and returns the numbers left and right of it
// e.g., "1-2" -> (1, 2)
tuple<uint, uint> parseSingleAssignment(const string& assignment) {
    auto pos = assignment.find('-');
    auto from = assignment.substr(0, pos);
    auto to = assignment.substr(pos + 1);

    return {stoi(from), stoi(to)};
}

/**
 * Holds the ranges of two Assignments
 * which sourced by one line of input data
 * e.g., "1-3,5-7"
 */
struct Assignment {
    // read as range [from,...,to] (inclusive)
    tuple<uint, uint> first;
    tuple<uint, uint> second;

    /**
     * Creates an Assignment from a string like "1-3,5-7"
     *
     * @param line
     * @return Assignment as (.first = 1-3, .second = 5-7)
     */
    static Assignment fromLine(const string& line) {
        auto first = make_tuple<uint, uint>(0, 0);
        auto second = make_tuple<uint, uint>(0, 0);
        auto comma = line.find(',');
        auto first_assignment = line.substr(0, comma);
        auto second_assignment = line.substr(comma + 1);

        Assignment self = {.first = parseSingleAssignment(first_assignment),
                           .second = parseSingleAssignment(second_assignment)};

        return self;
    }

    bool isContained() {
        return (
                // second in first
                (get<0>(second) >= get<0>(first) && get<1>(second) <= get<1>(first)) ||
                // first in second
                (get<0>(first) >= get<0>(second) && get<1>(first) <= get<1>(second))
                );
    }

    uint overlap() {
        auto& beginning_first = first;
        auto& beginning_second = second;

        // order the two assignments so that the first one has the lowest start id (`beginning_first`)
        if (get<0>(first) > get<0>(second)) {
            swap(beginning_first, beginning_second);
        }

        // we only overlap if the start of the later-starting is lower than the end of the second id
        if (get<0>(beginning_second) <= get<1>(beginning_first)) {
            auto& end = min(get<1>(beginning_first), get<1>(beginning_second));
            return end - get<0>(beginning_second) + 1;
        }

        return 0;
    }
};

std::string Day4::part1() {
    uint sum = 0;
    for(const auto& line: lines) {
        auto assignment = Assignment::fromLine(line);
        if (assignment.isContained()) {
            sum += 1;
        }
    }
    return to_string(sum);
}


std::string Day4::part2() {
   uint overlap_sum = 0;
    for(const auto& line: lines) {
         auto assignment = Assignment::fromLine(line);
         overlap_sum += assignment.overlap() > 0;
    }

    return to_string(overlap_sum);
}
