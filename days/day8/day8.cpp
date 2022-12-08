//
// Created by Richard Vogel on 08.12.22.
//
#include <iostream>
#include <map>
#include <set>
#include "day8.h"
#include "../../utils/misc.h"


using namespace std;

struct Wood {
    size_t width;
    size_t height;
    unique_ptr<uint[]> trees;

    static Wood buildFromInput(const vector<string> & lines) {
        size_t w = lines[0].size();
        size_t h = lines.size();
        auto trees = new uint[w * h];

        size_t curr_x;
        size_t curr_y = 0;
        for (auto& line : lines) {
            curr_x = 0;
            for(auto& c : line) {
                trees[curr_y * w + curr_x] = c - '0';
                curr_x++;
            }
            curr_y++;
        }
        return Wood {.width=w, .height=h, .trees=unique_ptr<uint[]>(trees)};
    }

    [[nodiscard]]
    bool isVisible (uint x, uint y) const {

        // increments in any direction
        vector<tuple<int, int>> directions = {
                {1, 0}, // +x-directiom
                {-1, 0}, // -x-direction
                {0, 1}, // +y-direction
                {0, -1} // -y-direction
        };

        // walk into all directions
        for (auto [dx, dy]: directions) {
            uint curr_height = getTree(x, y);
            uint curr_x = x;
            uint curr_y = y;
            while (true) {
                curr_x += dx;
                curr_y += dy;

                // we are out of bounds --> the tree is visible
                if (curr_x == width || curr_y == height ||
                    curr_x == -1 || curr_y == -1) {
                    return true;
                }

                // stop if we find a tree with same or higher score
                // (we can't see the tree because it is hidden)
                if (getTree(curr_x, curr_y) >= curr_height) {
                    break;
                }
            }
        }

        return false;
    }

    /**
     * product of smaller trees in any direction starting from the current tree
     *
    **/
    [[nodiscard]] uint scenicScore(uint x, uint y) const{
        // increments in any direction
        vector<tuple<int, int>> directions = {
                {1, 0}, // +x-directiom
                {-1, 0}, // -x-direction
                {0, 1}, // +y-direction
                {0, -1} // -y-direction
        };

        uint total_score = 1;

        // walk into all directions
        for (auto& [dx, dy]: directions) {
            uint curr_height = getTree(x, y);
            uint curr_x = x;
            uint curr_y = y;
            uint curr_score = 0;

            while (true) {
                curr_x += dx;
                curr_y += dy;

                // are we out of bounds?
                if (curr_x == width || curr_y == height ||
                    curr_x == -1 || curr_y == -1) {
                    break; // we reached the max total_score in that direction
                }


                // if we reach here, could move one step further -> increase total_score
                curr_score += 1;

                // stop if we find a tree with same or higher total_score
                // (we can't see the tree because it is hidden)
                if (getTree(curr_x, curr_y) >= curr_height) {
                    break;
                }

            }

            // total_score is the PRODUCT of all scores in all directions
            // cout << "Found a tree with score " << curr_score << " in direction " << dx << ", " << dy << endl;
            if (curr_score > 0) {
                total_score *= curr_score;
            }
        }

        return total_score;
    }
    /**
     * count all trees that are visible from any side of the wood
     * (i.e., the tree is not hidden in its row or column)
     * @return
     */
    [[nodiscard]] uint countVisibleTrees() const {
        uint count = 0;
        for (uint x = 0; x < width; x++) {
            for (uint y = 0; y < height; y++) {
                count += isVisible(x, y);
            }
        }
        return count;
    }

    [[nodiscard]]
    uint getTree(size_t x, size_t y) const {
        return trees[y * width + x];
    }

    /***
     * outputs the wood to the console
     */
    void printTree() {
        for (size_t y = 0; y < height; y++) {
            for (size_t x = 0; x < width; x++) {
                cout << getTree(x, y);
            }
            cout << endl;
        }
    }
};

Day8::Day8(const std::vector<std::string> &lines): Day(lines) {}


std::string Day8::part1() {
    auto wood = Wood::buildFromInput(lines);
    return to_string(wood.countVisibleTrees());
}


std::string Day8::part2() {
    auto wood = Wood::buildFromInput(lines);
    uint max_score = 0;
    for (uint x = 0; x < wood.width; x++) {
        for (uint y = 0; y < wood.height; y++) {
            uint curr_score = wood.scenicScore(x, y);
            if (curr_score > max_score) {
                //cout << "Found a new max score of " << curr_score << " at " << x << ", " << y << endl;
                max_score = curr_score;
            }
        }
    }

    return to_string(max_score);
}
