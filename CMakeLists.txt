cmake_minimum_required(VERSION 3.19.4)
project(advent_of_code_2022)

set(CMAKE_CXX_STANDARD 23)
add_definitions(-std=c++11)

add_executable(main.cpp utils/file.cpp utils/file.h utils/constants.h days/shared/base_day.cpp days/day2.h days/day1.h days/day1.cpp days/day2.cpp days/shared/base_day.h main.cpp utils/misc.cpp utils/misc.h)
