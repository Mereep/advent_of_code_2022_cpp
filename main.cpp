#include <iostream>
#include <vector>
#include "utils/file.h"
#include "days/day1.h"
#include "days/day2.h"

using namespace FileUtil;
using namespace MiscUtils;

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

    // Day2(std::vector<std::string>());
    //Day2 day2 = Day::fromFile<Day2>(workDirStr + "/data/day2.txt");
    //day2.play();
    //MiscUtils::playDay(inDay2);

    string inDay2 = FileUtil::readFile(workDirStr + "/data/day2.txt");
    auto lines2 = FileUtil::splitLines(inDay2);
    Day2 day2(lines2);
    cout << "Day 2" << endl << "=====" << endl;
    cout << "Part 1: " << day2.part1() << endl;
    cout << "Part 2: " << day2.part2() << endl;

    return 0;
}
