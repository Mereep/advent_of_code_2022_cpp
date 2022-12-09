//
// Created by Richard Vogel on 02.12.22.
//
#include <iostream>
#include <regex>
#include <string>

#include "file.h"
#include "misc.h"

using namespace std;
using namespace FileUtil;

#include "../days/day2/day2.h"

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

    string trim(const string& str) {
        auto leftTrimmed = regex_replace(str, regex("^\\s+"), string(""));
        return regex_replace(leftTrimmed, regex("\\s+$"), string(""));
    }

    string join(const vector<string>& elements, const string& sep) {
        string result;
        for (const string& element : elements) {
            result += element + sep;
        }
        return result.substr(0, result.size() - sep.size());
    }
}
