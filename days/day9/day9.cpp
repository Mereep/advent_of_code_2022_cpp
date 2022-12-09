//
// Created by Richard Vogel on 09.12.22.
//
#include <iostream>
#include <map>
#include <set>

#include "day9.h"
#include "../../utils/misc.h"


using namespace std;

/**
 * Represents something to do in the playing field
 * e.g., "R 4" means "move right 4 steps"
 */
struct Command {
    char dir;
    uint dist;

    static Command fromLine(const string& line) {
        auto trimLine = MiscUtils::trim(line);
        return Command {
            .dir = trimLine[0],
            .dist = static_cast<uint>(stoul(trimLine.substr(2)))
        };
    }
};


/**
 * Stores the field with all knots and the trace of the last knot
 */
struct Field {
    // all knots in the field (index 0 == the `head`)
    vector<tuple<int, int>> knots;

    // where we have been?
    set<tuple<int, int>> trace;

    /** creates a Field with n_knots knots (+ 1 for head) **/
    explicit Field(const uint n_knots): knots(n_knots + 1), trace({{0,0 }}) {}

    /** returns the tail at index `knot_idx` (hint: zero-indexed!) **/
    [[nodiscard]] const tuple<int, int>& getKnot(size_t knot_idx) const {
        return knots[knot_idx];
    }

    /** the distance in units in x-direction to the head **/
    [[nodiscard]] int xDist(const size_t knot_idx1, const size_t knot_idx2) const {
        return abs(get<0>(getKnot(knot_idx1)) - get<0>(getKnot(knot_idx2)));
    }

    /** the distance in units in y-direction to the head **/
    [[nodiscard]] int yDist(const size_t knot_idx1, const size_t knot_idx2) const {
        return abs(get<1>(getKnot(knot_idx1)) - get<1>(getKnot(knot_idx2)));
    }


    /** X-pos of a knot **/
    [[nodiscard]] int knotX(const size_t knot_idx) const {
        return get<0>(getKnot(knot_idx));
    }

    /** Y-pos of a knot **/
    [[nodiscard]] int knotY(const size_t knot_idx) const {
        return get<1>(getKnot(knot_idx));
    }


    /** are both head and tail are on the same row?
     * (i.e., same y-coordinate)
     * **/
    [[nodiscard]] bool is_same_row(const size_t knot_idx1, const size_t knot_idx2) const {
        return knotY(knot_idx1) == knotY(knot_idx2);
    }

    /** are both head and tail are on the same column?
     * (i.e., same x-coordinate)
     **/
    [[nodiscard]] bool is_same_col(const size_t knot_idx1, const size_t knot_idx2) const {
        return knotX(knot_idx1) == knotX(knot_idx2);
    }

    /** are the head and tail are adjacent?
     * (i.e., at the same row next to each other or one diagonal step away or at the very same position)
     */
    [[nodiscard]] bool are_adjacent(const size_t knot_idx1, const size_t knot_idx2) const {
        return is_same_row(knot_idx1, knot_idx2) && xDist(knot_idx1, knot_idx2) == 1 ||
               is_same_col(knot_idx1, knot_idx2) && yDist(knot_idx1, knot_idx2) == 1 ||
               xDist(knot_idx1, knot_idx2) == 1 && yDist(knot_idx1, knot_idx2) == 1 ||
               is_same_row(knot_idx1, knot_idx2) && is_same_col(knot_idx1, knot_idx2);
    }

    /** x-direction: we move to the right if the prev knot is right of us (and vise versa)**/
    [[nodiscard]] int dx(const uint knot_idx) const {
        if (knotX(knot_idx) == knotX(knot_idx - 1)) {
            return 0;
        }
        return knotX(knot_idx - 1) > knotX(knot_idx) ? 1 : -1;
    };

    /** y-direction we move down in y if the prev knot is above tail (and vise versa) **/
    [[nodiscard]] int dy(const uint knot_idx) const {
        if (knotY(knot_idx) == knotY(knot_idx - 1)) {
            return 0;
        }
        return knotY(knot_idx - 1) > knotY(knot_idx) ? 1 : -1;
    };

    /***
     * Will execute one concrete command
     * @param command
     */
    void execute(const Command& command) {
        // iterate over the commands steps
        for (int step_num = 0; step_num < command.dist; step_num++) {
            switch (command.dir) { // check the direction we want to move to
                case 'R':
                    knots[0] = {knotX(0) + 1, knotY(0)};
                    break;
                case 'L':
                    knots[0] = {knotX(0) - 1, knotY(0)};
                    break;
                case 'U':
                    knots[0] = {knotX(0), knotY(0) + 1};
                    break;
                case 'D':
                    knots[0] = {knotX(0), knotY(0) - 1};
                    break;
                default:
                    throw runtime_error("Unknown direction: " + to_string(command.dir));
            }

            // move each knot in direction of its next prev knot
            for (uint knot_idx = 1; knot_idx < knots.size(); knot_idx++) {

                // if they are touching each other, we have no movement --> nothing can happen
                if (are_adjacent(knot_idx, knot_idx - 1)) {
                    break;
                }

                knots[knot_idx] = {knotX(knot_idx) + dx(knot_idx), knotY(knot_idx) + dy(knot_idx)};
            }


            trace.insert(knots.back());
        }
    }
};

Day9::Day9(const std::vector<std::string> &lines): Day(lines) {}


std::string Day9::part1() {
    Field field(1);

    for (const auto& line: lines) {
       auto command = Command::fromLine(line);
       field.execute(command);
    }

    return to_string(field.trace.size());
}


std::string Day9::part2() {
    Field field(9);

    for (const auto& line: lines) {
        auto command = Command::fromLine(line);
        field.execute(command);
    }

    return to_string(field.trace.size());
}
