cmake_minimum_required(VERSION 3.19.4)
project(advent_of_code_2022)

set(CMAKE_CXX_STANDARD 23)
add_definitions(-std=c++11)

add_executable(
        main.cpp
        utils/misc.h
        utils/misc.cpp
        utils/file.cpp
        utils/file.h
        utils/constants.h
        days/shared/base_day.h
        days/shared/base_day.cpp
        days/day1/day1.cpp days/day1/day1.h
        days/day2/day2.cpp days/day2/day2.h
        days/day3/day3.cpp days/day3/day3.h
        days/day4/day4.cpp days/day4/day4.h
        days/day5/day5.cpp days/day5/day5.h
        days/day6/day6.cpp days/day6/day6.h
        days/day7/day7.cpp days/day7/day7.h
        days/day8/day8.cpp days/day8/day8.h
        days/day9/day9.cpp days/day9/day9.h
        days/day10/day10.cpp days/day10/day10.h
        main.cpp
        )
