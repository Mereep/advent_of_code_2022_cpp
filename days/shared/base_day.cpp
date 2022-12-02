//
// Created by Richard Vogel on 02.12.22.
//
#include <iostream>
#include "base_day.h"
#include "../../utils/file.h"

using namespace std;
Day::Day(const std::vector<std::string> &lines) {
    this->lines = lines;
}

void Day::play() {
    cout << "Part 1: " << part1() << endl;
    cout << "Part 2: " << part2() << endl;
}

template<class D>
D Day::fromFile(const std::string& path) {
    string inDay = FileUtil::readFile(path);
    const std::vector<string> inLines = FileUtil::splitLines(inDay);
    return D(inLines);
}
