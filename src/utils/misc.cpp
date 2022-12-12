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

    tuple<string, string> split(const string& str, const string& sep) {
        auto pos = str.find(sep);
        if (pos == string::npos) {
            return {str, ""};
        }
        return {str.substr(0, pos), str.substr(pos + sep.size())};
    }

    /** Splits lines on containers separated by lines being equal to sep **/
    vector<vector<string>> split_lines(const vector<string>& lines, const string& sep) {
        vector<vector<string>> result = {};
        vector<string> curr = {};
        for (const string& line : lines) {
            if (line == sep) {
                result.push_back(curr);
                curr = {};
            } else {
                curr.push_back(line);
            }
        }

        // add the last
        result.push_back(curr);

        return result;
    }

    vector<string> parse_regex(const string& line, const string& re) {
        vector<string> result = {};
        smatch match;
        string remainder = line;
        while (regex_search(remainder, match, regex(re))) {
            result.push_back(match.str(0));
            remainder = match.suffix();
        }
        return result;
    }

}
