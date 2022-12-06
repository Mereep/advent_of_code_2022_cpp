#include <iostream>
#include <vector>
#include "utils/file.h"
#include "days/day1/day1.h"
#include "days/day2/day2.h"
#include "days/day3/day3.h"
#include "days/day4/day4.h"
#include "days/day5/day5.h"
#include "days/day6/day6.h"

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
    cout << "Part 2: " << day1.part2() << endl;

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

    string inDay3 = FileUtil::readFile(workDirStr + "/data/day3.txt");
    auto lines3 = FileUtil::splitLines(inDay3);
    Day3 day3(lines3);
    cout << "Day 3" << endl << "=====" << endl;
    cout << "Part 1: " << day3.part1() << endl;
    cout << "Part 2: " << day3.part2() << endl;

    string inDay4 = FileUtil::readFile(workDirStr + "/data/day4.txt");
    auto lines4 = FileUtil::splitLines(inDay4);
    Day4 day4(lines4);
    cout << "Day 4" << endl << "=====" << endl;
    cout << "Part 1: " << day4.part1() << endl;
    cout << "Part 2: " << day4.part2() << endl;

    string inDay5 = FileUtil::readFile(workDirStr + "/data/day5.txt");
    auto lines5 = FileUtil::splitLines(inDay5);
    Day5 day5(lines5);
    cout << "Day 5" << endl << "=====" << endl;
    cout << "Part 1: " << day5.part1() << endl;
    cout << "Part 2: " << day5.part2() << endl;

    string inDay6 = FileUtil::readFile(workDirStr + "/data/day6.txt");
    auto lines6 = FileUtil::splitLines(inDay6);
    Day6 day6(lines6);
    cout << "Day 6" << endl << "=====" << endl;
    cout << "Part 1: " << day6.part1() << endl;
    cout << "Part 2: " << day6.part2() << endl;

    return 0;
}
