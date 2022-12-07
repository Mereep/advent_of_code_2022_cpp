//
// Created by Richard Vogel on 06.12.22.
//
#include <iostream>
#include <map>
#include <set>
#include "day7.h"
#include "../../utils/misc.h"

using namespace std;

Day7::Day7(const std::vector<std::string> &lines): Day(lines) {}

/***
 * entry type in a folder
 */
enum FolderEntryType {
    FOLDER_ENTRY,
    FILE_ENTRY
};

/***
 * An Entry in a Folder can be a  (sub-)folder or a file and if it is a file it has a size
 */
struct FolderEntry {
    // name of the entry
    string name;

    // subfolder or file?
    FolderEntryType type;

    // size of the file if it is a file
    uint size;
};

/***
 * Stores the state of the System
 * as in the current path we are in atm and all folders
 * we found
 */
struct FileSystem {
    // where we are atm (state)
    vector<string> current_path;

    // flat list of all folders we found in the FS
    map<vector<string>, std::vector<FolderEntry>> entries;

    /***
     * interprets a CLI output as needed
     * @param command
     */
    void interpret_shell_line(const string& command) {
        if (command.starts_with("$ cd")) { // switch directory
            auto index = command.find("cd");
            auto path = MiscUtils::trim(
                    command.substr(index + 3)
            );
            if (path == "..") { // Go "up" one level
                current_path.pop_back();
            } else { // Go "down" one level
                current_path.push_back(path);
            }
        } else if (command.starts_with("$ ls")) { // list directory
            // not interesting for us -> but the following stuff should be as listing
        } else if (command.starts_with("dir")) {
            auto dirname = MiscUtils::trim(command.substr(4));
            FolderEntry entry = {
                    .name = dirname,
                    .type = FOLDER_ENTRY,
                    .size = 0
            };

            // add it to the current folder
            if (entries.find(current_path) == entries.end()) {
                entries[current_path] = vector<FolderEntry>();
            }
            entries[current_path].push_back(entry);
        } else {
            // assume it is a file
            auto index = command.find(' ');
            auto filename = command.substr(index + 1);
            auto size = stoi(command.substr(0, index));

            // create the entry
            FolderEntry entry;
            entry.name = filename;
            entry.type = FILE_ENTRY;
            entry.size = size;

            // add it to the current folder
            if (entries.find(current_path) == entries.end()) {
                entries[current_path] = vector<FolderEntry>();
            }
            entries[current_path].push_back(entry);
        }
    }

    /***
     * returns the size of the folder
     * will count all files there and if there are folders inside decent into them and count their files' sizes
     *
     * @param path
     * @return
     */
    uint countFolderTotalSize(vector<string> path) {
        uint size = 0;
        for (auto &entry: entries[path]) {
            if (entry.type == FILE_ENTRY) {
                size += entry.size;
            } else {
                // it is a folder -> go down one level
                path.push_back(entry.name);
                size += countFolderTotalSize(path);
                path.pop_back();
            }
        }

        return size;
    }
};

std::string Day7::part1() {
    FileSystem fs;

    // interpret each line
    for (const auto& line : lines) {
        fs.interpret_shell_line(line);
    }

    uint total = 0;

    // find directories with a total sizes of 100'000 or LESS
    // and count the sum of these
    for (auto& entry: fs.entries) {
       auto val = fs.countFolderTotalSize(entry.first);
       if (val <= 100'000) {
           total += val;
       }
    }

    return to_string(total);
}


std::string Day7::part2() {
    FileSystem fs;

    // we need to free this amount of bytes
    const uint SPACE_TOTAL = 700'000'00;
    for (const auto& line : lines) {
        fs.interpret_shell_line(line);
    }

    const uint SPACE_FREE = SPACE_TOTAL - fs.countFolderTotalSize({"/"});
    const uint NEEDED_SPACE = 300'000'00 - SPACE_FREE;

    // the smallest folder which is at least DELETE_MIN bytes big in total
    uint smallest_matching_folder = -1;
    for (auto& entry: fs.entries) {
        auto val = fs.countFolderTotalSize(entry.first);

        // cout << "Folder " << MiscUtils::join(entry.first, "/").substr(1) << " has size " << val << endl;
        // update if it is bigger than DELETE_MIN and smaller than the current smallest folder
        if (val >= NEEDED_SPACE) {
            // cout << "...is big enough" << endl;
            if( val < smallest_matching_folder) {
                smallest_matching_folder = val;
                // cout << "...is smaller than the current smallest folder" << endl;
            }
        }
    }

    return to_string(smallest_matching_folder);
}
