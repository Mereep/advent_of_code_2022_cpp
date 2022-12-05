//
// Created by Richard Vogel on 05.12.22.
//

#include <string>
#include <iostream>
#include <map>
#include "day5.h"
#include <stack>
#include <regex>
#include <sstream>

using namespace std;

Day5::Day5(const std::vector<std::string> &lines): Day(lines) {}

string vectorOfCharsToString(vector<char>& lines) {
    std::stringstream s;
    for (char& c : lines) {
        s << c;
    }

    return s.str();
}
/**
 * will divide the input vector in a left and right half separated by a line matching pattern
 * e.g.,
 * ```
 * ab
 * cd
 *
 * ef
 * ```
 * will return two vectors: `{"ab", "cd"}` and `{"ef"}`
 * @param pattern
 * @param input
 * @return
 */
tuple<vector<string>, vector<string>> splitStringVectorAtPattern(const string& pattern, const vector<string>& input) {
    auto left = input.begin();
    auto right = input.end();
    auto middle = input.end();

    // find the pattern
    for (auto it = input.begin(); it != input.end(); it++) {
        if (*it == pattern) {
            middle = it;
            break;
        }
    }

    if (middle == input.end()) {
        throw runtime_error("pattern " + pattern + "not found");
    }

    return {vector(left, middle), vector(middle + 1 , right)};
}

/***
 * parses the stack over all lines (just one column at index(!) `stack_index`)
 * e.g. for the following input lines:
 * ```
 *     [D]
 * [N] [C]
 * [Z] [M] [P]
 * ```
 * becomes a stack of
 *  - N, Z if `stack_index` is 0
 *  - D, C, M if `stack_index` is 1,
 *  - P if `stack_index` is 2
 *
 * @param field
 * @param stack_index
 * @return
 */
stack<char> generateStack(const vector<string>& field, uint stack_index) {
    auto it = field.rbegin();
    stack<char> res;

    uint offset = 1 + stack_index * 4;
    while(it != field.rend()) {
        auto line = *it++;
        if (offset < line.size()) {
            string s = line.substr(offset, 1);
            if (s == " ") {
                break;
            }
            res.push(s[0]);
        }
    }
    return res;
}

/***
 * will return all numbers separated by whitespaces from the line
 * (e.g., "1 5 6" -> {1, 5, 6})
 * @param number_line
 * @return
 */
vector<uint> parseNumbers(const string& number_line) {
    const regex re = regex("\\d+");
    sregex_iterator numbers_str = sregex_iterator(number_line.begin(),
                                               number_line.end(),
                                                  re);

    std::sregex_iterator rend;

    vector<uint> numbers;

    while(numbers_str != rend) {
        auto match = *numbers_str++;
        numbers.push_back(stoi(match.str()));
    }

    return numbers;
}

/***
 * A instruction is a movement from stack `from` to stack `to`
 * whist `amount` items are moved
 */
struct Instruction {
    uint amount;
    uint from;
    uint to;
};

Instruction parseInstruction(const string& line) {
    regex s = regex(R"(move (\d+) from (\d+) to (\d+))");
    smatch m;
    regex_search(line, m, s);

    return {
        .amount = static_cast<uint>(stoi(m.str(1))),
        .from = static_cast<uint>(stoi(m.str(2))),
        .to = static_cast<uint>(stoi(m.str(3)))
    };
};


struct GameField {
    map<uint, stack<char>> stacks; // piles of objects
    vector<Instruction> instructions; // instructions to move objects
    uint currStep = 0;

    static GameField fromLines(const vector<string>& lines) {
        GameField self;

        // (i) split inout at the empty line separating the stacks from the instructions
        auto res = splitStringVectorAtPattern("", lines);
        auto left = get<0>(res);
        auto right = get<1>(res);

        auto number_line = *(left.end() - 1);

        // (ii) parse the number of stacks from the numbers line in the middle
        auto numbers = parseNumbers(number_line);
        left.pop_back();

        // (iii) parse each stack (row-wise)
        for (auto number: numbers) {
            self.stacks[number] = generateStack(left,
                                                number - 1 // index!
                                                );
        }

        // (iv) parse the instructions
        for (auto& line: right) {
            self.instructions.push_back(parseInstruction(line));
        }

        return self;
    }

    /** will move piece by piece */
    void step_type_9000() {
        // no instructions left
        if (currStep >= instructions.size()) {
            return;
        }

        auto& instruction = instructions[currStep];
        auto& from = stacks[instruction.from];
        auto& to = stacks[instruction.to];

        // remove one from stack and push to the other stack
        for (uint i = 0; i < instruction.amount; i++) {
            to.push(from.top());
            from.pop();
        }

        currStep++;
    }

    /** now we can move multiple pieces at once */
    void step_type_9001() {
        // no instructions left
        if (currStep >= instructions.size()) {
            return;
        }

        auto& instruction = instructions[currStep];
        auto& from = stacks[instruction.from];
        auto& to = stacks[instruction.to];

        // remove all stacks items in order and move the bunch at once
        // this transforms a STACK like {1, 2, 3, ...} into a VECTOR {3, 2, 1} (if amount = 3)
        vector<char> bunch;
        for (uint i = 0; i < instruction.amount; i++) {
           bunch.insert(bunch.begin(), from.top());
           from.pop();
        }

        for (auto& item: bunch) {
            to.push(item);
        }

        currStep++;
    }

    [[nodiscard]] uint instructionCount() const {
        return static_cast<uint>(instructions.size());
    }

    vector<char> topRow() {
        vector<char> top_row;
        for (auto& stack: stacks) {
            if (stack.second.empty()) {
                top_row.push_back(' ');
            } else {
                top_row.push_back(stack.second.top());
            }
        }
        return top_row;
    }
};

std::string Day5::part1() {
    GameField field = GameField::fromLines(lines);
    while(field.currStep < field.instructionCount()) {
        field.step_type_9000();
    }

    auto top_row = field.topRow();

    return vectorOfCharsToString(top_row);
}


std::string Day5::part2() {
    GameField field = GameField::fromLines(lines);
    while (field.currStep < field.instructionCount()) {
        field.step_type_9001();
    }

    auto top_row = field.topRow();

    return vectorOfCharsToString(top_row);
}
