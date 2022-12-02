//
// Created by Richard Vogel on 01.12.22.
//
#include <fstream>
#include <vector>
#include <iostream>
#include <sstream>

using namespace std;

namespace FileUtil {
    std::string readFile(const std::string& path) {
        std::fstream file(path.c_str(), std::ios::in);
        if (!file || !file.good()) {
            throw std::runtime_error("Could not open file: " + path);
        }
        file.seekg(0, std::ios::end);
        auto len = file.tellg();
        file.seekg(0, std::ios::beg);
        // read the file
        char* buffer = new char[len];
        file.read(buffer, len);
        file.close();
        std::string content(buffer, len);

        return  content;
    }

    std::vector<std::string> splitLines(std::string& input) {
        std::vector<std::string> lines;
        std::string line;
        std::istringstream f(input);
        while (std::getline(f, line)) {
            lines.push_back(line);
        }
        return lines;
    }
}

