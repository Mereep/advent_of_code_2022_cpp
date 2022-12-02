cmake_minimum_required(VERSION 3.19.4)
project(advent_of_code_2022)

set(CMAKE_CXX_STANDARD 23)

add_executable(advent_of_code_2022 main.cpp utils/file.cpp utils/file.h utils/constants.h days/shared/base_day.cpp days/day1.cpp days/day1.h days/shared/base_day.h)
