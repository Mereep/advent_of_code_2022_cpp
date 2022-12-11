//
// Created by Richard Vogel on 11.12.22.
//
#include "day11.h"
#include <vector>
#include <map>
#include "../../utils/misc.h"

typedef unsigned int uint;

using namespace std;


Day11::Day11(const std::vector<std::string> &lines): Day(lines) {}

/** an Item the monkeys stole **/
struct Item {
    long worry_level;
};

/** which types can be used as an operation on Items? */
enum OperationType {
    PLUS,
    MINUS,
    MULTIPLY,
    SQUARE
};

/** defines an operation that can be applied to a number
 * represents a line like `new = old * 19`
 * */
struct Operation {
    OperationType op;
    long value;

    /** parses a line like Operation: new = old * 19
     * @param operation
     * @return
     */
    static Operation fromLine(string operation) {
        operation = MiscUtils::trim(operation);
        if (operation.starts_with("Operation: new = old +")) {
            long number = stoi(operation.substr(23));
            return Operation {
                .op = PLUS,
                .value = number
            };

        } else if (operation.starts_with("Operation: new = old -")) {
            long number = stoi(operation.substr(23));
            return Operation {
                .op = MINUS,
                .value = number
            };

        } else if (operation.starts_with("Operation: new = old * old")) {
            return Operation {
                    .op = SQUARE,
                    .value = 0,
            };

        } else if (operation.starts_with("Operation: new = old *")) {
            long number = stoi(operation.substr(23));
            return Operation {
                .op = MULTIPLY,
                .value = number
            };


        } else {
            throw runtime_error("Unknown operation: " + operation);
        }
    }

    /** apply this operation to the given number **/
    [[nodiscard]] long apply(long number) const {
        switch (op) {
            case PLUS:
                return number + value;

            case MINUS:
                return number - value;

            case SQUARE:
                return number * number;

            case MULTIPLY:
                return number * value;
        }
    }
};

// which tests we support?
enum TestType {
    DIVISIBLE_BY
};

/** represents an operation like
 * ```Test: divisible by 19
    If true: throw to monkey 2
    If false: throw to monkey 0
    ```
    means an operation that can be applied to a number
    and depending on the outcome of the operation a monkey is assigned
 */
struct Test {
    TestType type;
    long value;

    map<int, uint> result_to_monkey_mapping;

    uint get_monkey(long score) {
        if (type == DIVISIBLE_BY) {
            if (score % value == 0) {
                return result_to_monkey_mapping.at(1);
            } else {
                return result_to_monkey_mapping.at(0);
            }
        } else {
            throw runtime_error("Unknown test type");
        }
    }

    static Test fromLines(const vector<string>& lines) {
        string test_line = MiscUtils::trim(lines[0]);
        if (test_line.starts_with("Test: divisible by")) {
            long number = stoi(test_line.substr(18));
            string true_line = MiscUtils::trim(lines[1]);
            string false_line = MiscUtils::trim(lines[2]);

            return Test {
                .type = DIVISIBLE_BY,
                .value = number,
                .result_to_monkey_mapping = {
                    {1, stoi(true_line.substr(25))},
                    {0, stoi(false_line.substr(26))},
                }
            };
        } else {
            throw runtime_error("Unknown test: " + test_line);
        }
    }
};

/*** one Monkey does some Operation on worry levels, has some Items and tests the operation to decide where to throw
 * it next
 */
struct Monkey {
    vector<Item> items;
    Operation operation;
    Test test;

    // we need to count how often a monkey has thrown for the results
    uint thrown_items = 0;
};

/*** Playing field with some monkeys **/
struct MonkeyLand {

    // the actual monkeys
    vector<Monkey> monkeys;

    // we need this to keep worry levels tamed
    long divisor_product = 0;

    // we do not need that (just for debugging)
    uint round = 0;

    static MonkeyLand from_input(const vector<string> &lines) {
        MonkeyLand land = {.monkeys = {}};

        // retrieve all monkey-inputs as separate vectors
        auto monkeys_in = MiscUtils::split_lines(lines, "");
        long divisor_product = 1;

        // build each monkey...
        for (auto monkey_in : monkeys_in) {
            Monkey monkey;

            // parse the starting items
            const string& items_in = monkey_in.at(1);
            const auto numbers_str = MiscUtils::parse_regex(items_in, "\\d+");
            vector<Item> items = {};
            for (const auto& number : numbers_str) {
                items.emplace_back(Item{.worry_level = stoi(number)});
            }

            // get the operation
            const string& operation_in = MiscUtils::trim(monkey_in.at(2));

            // get the Test
            vector<string> remainder = vector(monkey_in.begin() + 3, monkey_in.end());

            monkey.items = items;
            monkey.operation = Operation::fromLine(operation_in);
            monkey.test = Test::fromLines(remainder);
            land.monkeys.emplace_back(monkey);
            divisor_product *= monkey.test.value;
            land.divisor_product = divisor_product;
        }

        return land;
    }

    /** let all monkeys throw once in order **/
    void do_round(bool reduce_worry_level) {
        round++;
        for (auto& monkey: monkeys) {
            // each item is taken once
            for (auto item: monkey.items) {
                // we apply the operation on the item
                long result = monkey.operation.apply(item.worry_level);

                // and (optionally) reduce the worry level
                if (reduce_worry_level) result /= 3;

                // check which monkey gets the item (by applying the Test)
                uint new_monkey = monkey.test.get_monkey(result);

                auto result_new = result;
                // keep the worry-level small enough
                if(result >= divisor_product) {
                    result_new = result - ((result / divisor_product) * divisor_product);

                    // this is a sanity test for debugging
                    // (new result should yield the same remainder for all divisors)
                    /*
                    for(auto& monkey2: monkeys) {
                        if (result % monkey2.test.value != result_new % monkey2.test.value) {
                            throw runtime_error("asldkaslök");
                        }

                    }*/

                }

                // hand over the item
                monkeys.at(new_monkey).items.emplace_back(Item{.worry_level = result_new});

                // each item counts as throw
                monkey.thrown_items++;
            }

            // the monkey looses its own items (it throws them all)
            monkey.items = {};
        }
    }
};

std::string Day11::part1() {
    MonkeyLand ml = MonkeyLand::from_input(lines);

    // play 20 rounds
    for(uint i = 0; i < 20; i++) {
        ml.do_round(true);
    }

    // find the two highest worry-levels
    vector<uint> throw_counts = {};
    for(const auto& monkey: ml.monkeys) {
        throw_counts.emplace_back(monkey.thrown_items);
    }
    sort(throw_counts.begin(), throw_counts.end());

    // and return
    return to_string(throw_counts.at(throw_counts.size() - 1) * throw_counts.at(throw_counts.size() - 2));
}


std::string Day11::part2() {
    MonkeyLand ml = MonkeyLand::from_input(lines);

    // as part one but 10k rounds
    for(uint i = 0; i < 10'000; i++) {
        ml.do_round(false);
    }

    vector<long> throw_counts = {};
    for(const auto& monkey: ml.monkeys) {
        throw_counts.emplace_back(monkey.thrown_items);
    }

    sort(throw_counts.begin(), throw_counts.end());
    return to_string(throw_counts.at(throw_counts.size() - 1) * throw_counts.at(throw_counts.size() - 2));
}
