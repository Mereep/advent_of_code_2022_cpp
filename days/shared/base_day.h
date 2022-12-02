//
// Created by Richard Vogel on 02.12.22.
//

#ifndef ADVENT_OF_CODE_2022_BASE_DAY_H
#define ADVENT_OF_CODE_2022_BASE_DAY_H

#include <string>
#include <vector>

class Day {
protected:
    std::vector<std::string> lines;
public:

    explicit Day(const std::vector<std::string> &lines);

    virtual std::string part1() = 0;
    virtual std::string part2() = 0;

    virtual ~Day() = default;

    void play();

    template<class D>
    static D fromFile(const std::string& path);
};
#endif //ADVENT_OF_CODE_2022_BASE_DAY_H
