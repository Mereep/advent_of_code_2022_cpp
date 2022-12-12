cmake_minimum_required(VERSION 3.19.4)
project(advent_of_code_2022)

# set(CMAKE_CXX_STANDARD 23)
add_executable(
        aoc
        src/main.cpp
        src/utils/misc.cpp
        src/utils/file.cpp
        src/days/shared/base_day.cpp
        src/days/day1/day1.cpp
        src/days/day2/day2.cpp
        src/days/day3/day3.cpp
        src/days/day4/day4.cpp
        src/days/day5/day5.cpp
        src/days/day6/day6.cpp
        src/days/day7/day7.cpp
        src/days/day8/day8.cpp
        src/days/day9/day9.cpp
        src/days/day10/day10.cpp
        src/days/day11/day11.cpp
        src/days/day12/day12.cpp
        )

target_compile_features(aoc PRIVATE cxx_std_20)
