//
// Created by Richard Vogel on 10.12.22.
//
#include <iostream>
#include <map>
#include <utility>
#include <sstream>
#include "day10.h"
#include "../../utils/misc.h"

/**
 * Represents one command tha `Cpu` can execute
 */
struct Command {
    /** as in addx, subx, etc. **/
    string name;

    /** as in r1, r2, etc. **/
    int value;

    static Command fromString(const string& line) {
        const auto [first, second] = MiscUtils::split(line, " ");
        if(second.empty()) {
            return Command {
                .name = first,
                .value = 0
            };
        }

        return Command {
            .name = first,
            .value = stoi(second)
        };
    }

    /** how many cycles a command needs **/
    [[nodiscard]] int cycles() const {

        if(name == "addx") {
            return 2;
        }

        if(name == "noop") {
            return 1;
        }

        throw runtime_error("Don't know cycle length for: " + name);
    }
};

struct Cpu {
    /** stores the registers' value over cycles
     * as in ('x' -> [0, 10, -2, 0, ....])
     **/
    map<string, vector<int>> cycle_history;

    /** all registers the machine could have */
    vector<string> available_registers;

    /** the result of the last command indexed by its registers (if any) */
    map<string, int> computationalResult;

    /**
     * the CPU model
     * @param available_registers (which registers the machine supports)
     */
    explicit Cpu(vector<string> available_registers) {
        this->available_registers = std::move(available_registers);
        cycle_history = {};

        for(const auto& reg: this->available_registers) {
            cycle_history[reg] = {};
        }
    }

    /**
     * Execution of one command.
     * @param command
     */
    void execute(const Command& command) {

        // fill with default value for the amount of cycles the command takes
        for (int i = 0; i < command.cycles(); i++) {
            for (const auto& reg : available_registers) {
                cycle_history[reg].push_back(current_value(reg));
            }
        }

       if (command.name.starts_with("add")) {
           string reg = command.name.substr(command.name.size() - 1);
            computationalResult[reg] = current_value(reg, true) + command.value;
       }

       else if(command.name.starts_with("noop")) {
           // do nothing
       } else {
           throw runtime_error("Don't know how to execute: " + command.name);
       }

    }

    /**
     * Will return the value of the register at a given cycle number (1-indexed!)
     * may be a cycle in the future under the assumption nothing happened until then
     * @param time
     * @param reg
     * @return
     */
    int value_at_time(uint time, const string& reg) {
        if (time <= cycle_history[reg].size()) {
            return cycle_history[reg][time - 1];
        }

        if (computationalResult.find(reg) != computationalResult.end()) {
            return computationalResult[reg];
        }

        return *cycle_history[reg].end();
    }

    /** current registers' value
     * this might be the last value found OR a computed value from a last command
     * if consume = true and it was an old command, we remove it from the map
     * **/
    [[nodiscard]] int current_value(const string& register_name, bool consume=false)  {

        // default case: register is not yet initialized (== 1)
        if (cycle_history.at(register_name).empty()) {
            return 1;
        }

        // if we have a result incoming at this step, use it
        if (computationalResult.find(register_name) != computationalResult.end()) {
            int res = computationalResult[register_name];
            // remove the mapping entry for this register_name
            if (consume) {
                computationalResult.erase(register_name);
            }
            return res;
        }

        // otherwise, return the last value
        return cycle_history.at(register_name).back();
    }
};

Day10::Day10(const std::vector<std::string> &lines): Day(lines) {}


std::string Day10::part1() {
    int res = 0;

    Cpu cpu = Cpu({"x"});
    for (const auto& line : lines) {
        const Command command = Command::fromString(line);
        cpu.execute(command);
    }

    for (int i = 20; i < cpu.cycle_history["x"].size(); i += 40) {
        int value = cpu.value_at_time(i, "x");
        // cout << "x[" << i-1 << "] = " << value << endl;
        res += i * value;
    }

    return to_string(res);
}


std::string Day10::part2() {
    Cpu cpu = Cpu({"x"});
    for (const auto& line : lines) {
        const Command command = Command::fromString(line);
        cpu.execute(command);
    }

    // create an array with 60 * 4 elements representing the pixels on a crt screen
    bool screen[40 * 6] = {};

    for (int i = 0; i <= cpu.cycle_history["x"].size(); i++) {
        int sprite_position = cpu.value_at_time(i + 1, "x");
        uint screen_pos = i % (40 * 6);
        uint screen_x = screen_pos % 40;

        if (sprite_position == screen_x || sprite_position + 1 == screen_x || sprite_position - 1 == screen_x) {
            screen[screen_pos] = true;
        }
    }

    std::stringstream ss;
    ss << endl;
    for(uint y = 0; y < 6; y++) {
        for(uint x = 0; x < 40; x++) {
            ss << (screen[x + y * 40] ? "#" : " ");
        }
        ss << endl;
    }

    return ss.str();
}
