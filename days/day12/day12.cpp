//
// Created by Richard Vogel on 12.12.22.
//
#include "day12.h"
#include <vector>
#include <map>
#include <iostream>
#include "../../utils/misc.h"

// map for directions to move to
const vector<tuple<size_t, size_t>> directions = {
        {0, - 1}, // up
        {0, + 1}, // down
        {-1, 0}, // left
        {+1, 0}  // right
};

/** represents one playing field **/
struct Field {
    unsigned int elevation;

    // shortest path we found
    // hint: defaults to maximum value possible due to underflow
    unsigned int shortest_dist = -1;

    bool is_start;
    bool is_finish;

    bool visited = false;
};

struct HeightMap {
    vector<shared_ptr<Field>> fields;
    size_t width, height;

    // If we find a path to the finish, we store the distance here
    // this saves us time if our current path is already longer
    // hint: defaults to maximum value due to underflow
    unsigned long global_shortest_path = -1;

    static HeightMap fromInput(const vector<string>& lines) {
        HeightMap map = {
            .fields = {},
            .width = lines[0].size(),
            .height = lines.size()
        };

        for(const auto& line: lines) {
            for (const auto& h: line) {
                if (h == 'S') {
                    map.fields.push_back(make_shared<Field>(Field {
                        .elevation = 'a' -  'a', // min elevation (i.e. 0),
                        .is_start = true,
                        .is_finish = false
                    }));
                } else if (h == 'E') {
                    map.fields.push_back(make_shared<Field>(Field {
                        .elevation =  'z' - 'a', // max elevation
                        .is_start = false,
                        .is_finish = true
                    }));
                } else {
                    map.fields.push_back(make_shared<Field>(Field {
                        .elevation = static_cast<unsigned int>(h - 'a'),
                        .is_start = false,
                        .is_finish = false
                    }));
                }
            }
        }
        return map;
    }

    /** returns the field height at the given position **/
    [[nodiscard]] unsigned int get_elevation(size_t x, size_t y) const {
        return get_field(x, y)->elevation;
    }

    [[nodiscard]] shared_ptr<Field> get_field(size_t x, size_t y) const {
        return fields.at(y * width + x);
    }

    [[nodiscard]] shared_ptr<Field> get_field_at_index(size_t index) const {
        return fields.at(index);
    }

    // which index is the start field at?
    [[nodiscard]] size_t get_start_field_pos() const {
        for (size_t i = 0; i < fields.size(); i++) {
            if (fields.at(i)->is_start) {
                return i;
            }
        }
        throw runtime_error("no start field found");
    }
    // which index is the finish field at??
    [[nodiscard]] size_t get_finish_field_pos() const {
        for (size_t i = 0; i < fields.size(); i++) {
            if (fields.at(i)->is_finish) {
                return i;
            }
        }
        throw runtime_error("no start field found");
    }

    // transforms a flat index to coordinates
    [[nodiscard]] tuple<size_t, size_t> index_to_coordinates(size_t index) const {
        return {index % width, index / width};
    }

    /** starts a deoth first search **/
    void run() {
        auto start = get_start_field_pos();
        follow(start, 0);
    }

    /** follows a path from the given field
     * goes in all directions and checks if the path is shorter than the current shortest to this field
     * **/
    void follow(size_t current_idx, unsigned long current_cost) {
        auto [x, y] = index_to_coordinates(current_idx);
        auto curr_field = get_field(x, y);

        // for one path we visit only once with a shorter distance
        if (curr_field->visited && current_cost >= curr_field->shortest_dist) {
            return;
        }

        if (curr_field->shortest_dist < current_cost || current_cost >= global_shortest_path) {
            // we already found a shorter path (to this place or globally)
            return;
        }

        curr_field->shortest_dist = current_cost;
        auto curr_elevation = curr_field->elevation;

        // we move to each direction
        for(auto& [dx, dy]: directions) {
            auto new_x = x + dx;
            auto new_y = y + dy;

            // check if we run out of bounds
            if (new_x == -1 || new_x == width || new_y == -1 || new_y == height) {
                continue;
            }

            // get the field and its info
            auto new_idx = new_y * width + new_x;
            auto new_field = get_field_at_index(new_idx);
            auto new_elevation = new_field->elevation;

            // we can only step exactly one step up (but: down all the way possible)
            if (new_elevation > curr_elevation + 1) {
                // we can't go there
                continue;
            }

            if (new_field->is_finish) {
                // we found a path to the finish
                global_shortest_path = current_cost + 1;
                //cout << "found path with length " << global_shortest_path << endl;
                return;
            }

            curr_field->visited = true;

            // follow down the next road
            follow(new_idx, current_cost + 1);

        }
    }

    /** forgets the current visited-state **/
    void reset_visited() {
        for (auto& field: fields) {
            field->visited = false;
            // field->shortest_dist = -1;
        }
    }
};

Day12::Day12(const std::vector<std::string> &lines): Day(lines) {}

std::string Day12::part1() {
    HeightMap map = HeightMap::fromInput(lines);
    map.run();
    return to_string(map.global_shortest_path);
}

std::string Day12::part2() {
    HeightMap h = HeightMap::fromInput(lines);
    auto start_pos_idx = h.get_start_field_pos();
    auto start_pos = h.get_field_at_index(start_pos_idx);

    // patch start position as we want to start at every `a`
    start_pos->elevation = 0;

    vector<size_t> all_a_positions = {};
    for (size_t i = 0; i < h.fields.size(); i++) {
        auto field = h.get_field_at_index(i);
        if (field->elevation == 0) {
            all_a_positions.push_back(i);
        }
    }

    unsigned long min_path = 391; // result from above

    // follow all paths with an `a`
    for (auto& a_pos: all_a_positions) {
        // we want to revisit everything but we do not necessarily follow all paths again
        // if we come to a path we visited already with a shorter distance
        h.reset_visited();

        // we want to find a shorter path, so we can set this guy as minimum
        h.global_shortest_path = min_path;
        h.follow(a_pos, 0);
        // cout << "found path with length " << h.global_shortest_path << endl;
        if (h.global_shortest_path < min_path) {
            min_path = h.global_shortest_path;
        }
    }
    return to_string(min_path);
}
