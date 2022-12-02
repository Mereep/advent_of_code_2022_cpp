//
// Created by Richard Vogel on 02.12.22.
//
#include "file.h"
#include <iostream>
#include "misc.h"

using namespace std;
using namespace FileUtil;

#include "../days/day2.h"

namespace MiscUtils {

    template<class D>
    void playDay(const std::string& inputFile) {
        string inDay = FileUtil::readFile(inputFile);
        const std::vector<string> lines = FileUtil::splitLines(inDay);

        D d = D(lines);
        // cout << "Day 1" << endl << "=====" << endl;
        cout << "Part 1: " << d.part1() << endl;
        cout << "Part 2: " << d.part2() << endl;
    }

}
