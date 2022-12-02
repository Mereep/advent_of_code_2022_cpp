//
// Created by Richard Vogel on 02.12.22.
//
#ifndef ADVENT_OF_CODE_2022_FILE_H
#define ADVENT_OF_CODE_2022_FILE_H

#include <string>

using namespace std;
namespace FileUtil {
    std::string readFile(const std::string& path);
    std::vector<std::string> splitLines(std::string& input);

}
#endif //ADVENT_OF_CODE_2022_FILE_H
