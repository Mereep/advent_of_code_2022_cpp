#include <iostream>
#include <vector>
#include "utils/file.h"
#include "days/day1.h"

using namespace FileUtil;
int main() {
    char* workDir = getenv("WORK_DIR");
    if (workDir == nullptr) {
        std::cout << "specify a `WORK_DIR` env variable" << std::endl;
        return 1;
    }
    string workDirStr(workDir);


    string inDay1 = FileUtil::readFile(workDirStr + "/data/day1.txt");
    auto lines = FileUtil::splitLines(inDay1);
    Day1 day1(lines);
    cout << "Day 1" << endl << "=====" << endl;
    cout << "Part 1: " << day1.part1() << endl;
    cout << "Part 2: " <<day1.part2() << endl;

    return 0;
}
