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
        days/day1.cpp days/day1.h
        days/day2.cpp days/day2.h
        days/day3.cpp days/day3.h
        days/day4.cpp days/day4.h
        days/day5.cpp days/day5.h
        main.cpp
)
