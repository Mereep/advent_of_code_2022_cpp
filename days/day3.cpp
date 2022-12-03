//
// Created by Richard Vogel on 02.12.22.
//

#include <string>
#include <iostream>
#include <map>
#include "day3.h"

using namespace std;


// mapping of letter -> count, e.g., 'c' -> 1
// symbolizes 1 Rucksack
typedef map<char, uint> rucksack_content1_t;

// just two Rucksacks
typedef tuple<rucksack_content1_t, rucksack_content1_t> rucksack_content2_t;

Day3::Day3(const std::vector<std::string> &lines) : Day(lines) {}

/***
 * Counts the occurrences of letters in the string
 *
 * @param line
 * @return Rucksack content is mapping of letter -> count, e.g., 'c' -> 1
 */
rucksack_content1_t countContents1(const string &line) {
    rucksack_content1_t contents;
    auto lenRucksack = line.length();
    for (uint i = 0; i < lenRucksack; i++) {
        char c = line[i];

        auto pos = contents.find(c);

        if (pos == contents.end()) {
            contents.insert({c, 1});
        } else {
            contents[c] += 1;
        }
    }

    return contents;
}

/***
 * Each letter has a score as per task (a-z) = 1-26; A-Z = 27-52
 * @param c
 * @return score for `c`
 */
uint priority(char c) {
    if ('a' <= c && 'z' >= c) {
        return c - 'a' + 1;
    }

    if ('A' <= c && 'Z' >= c) {
        return c - 'A' + 27;
    }

    throw std::invalid_argument("Invalid character: " + to_string(c));
}

/***
 * counts the occurrences of letters in the string
 * the string will be interpreted as two inputs of same length
 * @param: line of letters / items
 * @return: two rucksack contents as mapping letter -> count
 */
rucksack_content2_t countContents2(const string &line) {
    uint lenRucksack = int(line.length() / 2);
    rucksack_content1_t rucksack1 = countContents1(line.substr(0, lenRucksack));
    rucksack_content1_t rucksack2 = countContents1(line.substr(lenRucksack, 2 * lenRucksack));

    return make_pair(rucksack1, rucksack2);
}

std::string Day3::part1() {
    uint sum = 0;

    // iterate over all lines
    for (const string &line: lines) {
        // interpret line as two rucksacks
        auto contents = countContents2(line);
        // .. and get the contents of each rucksack
        auto contents1 = get<0>(contents);
        auto contents2 = get<1>(contents);

        // check if the item is inside both rucksacks
        for (auto &[item, _]: contents1) {
            if (contents2.find(item) != contents2.end()) {
                // get the priority of the 2-times item
                sum += priority(item);
            }
        }
    }

    return to_string(sum);
}

std::string Day3::part2() {

    // each 3 lines make up one chunk of 3 Elves
    auto n_lines = lines.size();
    uint n_chunks = int(n_lines / 3);
    uint sum = 0;

    for (uint chunk = 0; chunk < n_chunks; chunk++) {
        // get all 3 Rucksacks for this chunk
        auto contents1 = countContents1(lines[chunk * 3 + 0]);
        auto contents2 = countContents1(lines[chunk * 3 + 1]);
        auto contents3 = countContents1(lines[chunk * 3 + 2]);

        // iterate over one of the rucksack
        for (auto &[item, _]: contents1) {
            // and find an item which is in all 3 of them (the iterated one and the other two)
            if (contents2.find(item) != contents2.end() && contents3.find(item) != contents3.end()) {
                // get the priority of the 3-times item
                sum += priority(item);
                continue; // we only count one occurrence
            }
        }
    }

    return to_string(sum);
}
