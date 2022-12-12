//
// Created by Richard Vogel on 02.12.22.
//

#ifndef ADVENT_OF_CODE_2022_MISC_H
#define ADVENT_OF_CODE_2022_MISC_H

namespace MiscUtils {
    template<class D>
    void playDay(const std::string&);
    std::string trim(const std::string& str);
    std::string join(const std::vector<std::string>&, const std::string&);
    std::tuple<std::string, std::string> split(const std::string&, const std::string&);
    std::vector<std::vector<std::string>> split_lines(const std::vector<std::string>&, const std::string&);
    std::vector<std::string> parse_regex(const std::string&, const std::string&);
    }
#endif //ADVENT_OF_CODE_2022_MISC_H
