#include <iostream>
#include <vector>
#include "utils/file.h"
#include "days/day1/day1.h"
#include "days/day2/day2.h"
#include "days/day3/day3.h"
#include "days/day4/day4.h"
#include "days/day5/day5.h"
#include "days/day6/day6.h"
#include "days/day7/day7.h"
#include "days/day8/day8.h"
#include "days/day9/day9.h"
#include "days/day10/day10.h"
#include "days/day11/day11.h"
#include "days/day12/day12.h"


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



    string inDay2 = FileUtil::readFile(workDirStr + "/data/day2.txt");
    auto lines2 = FileUtil::splitLines(inDay2);
    Day2 day2(lines2);
    cout << "Day 2" << endl << "=====" << endl;
    cout << "Part 1: " << day2.part1() << endl;
    cout << "Part 2: " << day2.part2() << endl;

    //Day2(std::vector<std::string>());
    // Day2 day = Day::fromFile<Day2>(workDirStr + "/data/day2.txt");
    // day2.play();
    //MiscUtils::playDay(inDay2);

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

    string inDay7 = FileUtil::readFile(workDirStr + "/data/day7.txt");
    auto lines7 = FileUtil::splitLines(inDay7);
    Day7 day7(lines7);
    cout << "Day 7" << endl << "=====" << endl;
    cout << "Part 1: " << day7.part1() << endl;
    cout << "Part 2: " << day7.part2() << endl;

    string inDay8 = FileUtil::readFile(workDirStr + "/data/day8.txt");
    auto lines8 = FileUtil::splitLines(inDay8);
    Day8 day8(lines8);
    cout << "Day 8" << endl << "=====" << endl;
    cout << "Part 1: " << day8.part1() << endl;
    cout << "Part 2: " << day8.part2() << endl;

    string inDay9 = FileUtil::readFile(workDirStr + "/data/day9.txt");
    auto lines9 = FileUtil::splitLines(inDay9);
    Day9 day9(lines9);
    cout << "Day 9" << endl << "=====" << endl;
    cout << "Part 1: " << day9.part1() << endl;
    cout << "Part 2: " << day9.part2() << endl;

    string inDay10 = FileUtil::readFile(workDirStr + "/data/day10.txt");
    auto lines10 = FileUtil::splitLines(inDay10);
    Day10 day10(lines10);
    cout << "Day 10" << endl << "=====" << endl;
    cout << "Part 1: " << day10.part1() << endl;
    cout << "Part 2: " << day10.part2() << endl;


    string inDay11 = FileUtil::readFile(workDirStr + "/data/day11.txt");
    auto lines11 = FileUtil::splitLines(inDay11);
    Day11 day11(lines11);
    cout << "Day 11" << endl << "=====" << endl;
    cout << "Part 1: " << day11.part1() << endl;
    cout << "Part 2: " << day11.part2() << endl;

    string inDay12 = FileUtil::readFile(workDirStr + "/data/day12.txt");
    auto lines12 = FileUtil::splitLines(inDay12);
    Day12 day12(lines12);
    cout << "Day 12" << endl << "=====" << endl;
    cout << "Part 1: " << day12.part1() << endl;
    cout << "Part 2: " << day12.part2() << endl;


    return 0;
}
