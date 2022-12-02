//
// Created by Richard Vogel on 02.12.22.
//

#ifndef ADVENT_OF_CODE_2022_DAY1_H
#define ADVENT_OF_CODE_2022_DAY1_H

#include "shared/base_day.h"

class Day1 : public Day {
public:
    explicit Day1(const std::vector<std::string> &lines);
    std::string part1() override;
    std::string part2() override;
};


#endif //ADVENT_OF_CODE_2022_DAY1_H
