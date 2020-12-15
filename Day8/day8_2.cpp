#include <tuple>
#include <vector>
#include <fstream>
#include <iostream>
#include <unordered_map>

int main() {
    std::ifstream ifs("day8_input.txt");
    if (!ifs) {
        std::cout << "Failed to open the input file." << std::endl;
        return 1;
    }

    std::string read_line;
    std::vector<std::pair<std::pair<std::string, int>, bool>> instructions;

    while (!ifs.eof()) {
        std::getline(ifs, read_line);
        instructions.emplace_back(
            std::make_pair(read_line.substr(0, 3), std::stoi(read_line.substr(4, read_line.length() - 4))), false);
    }

    int accumulator { 0 };
    int target_iterator { 0 };
    bool is_changed { false };
    std::unordered_map<int, bool> changed_positions;
    std::vector<std::pair<std::pair<std::string, int>, bool>> instructions_backup = instructions;

    while (true) {
        if (instructions.size() - 1 <= target_iterator) break;

        if (instructions[target_iterator].second) {
            is_changed      = false;
            accumulator     = 0;
            target_iterator = 0;
            instructions    = instructions_backup;
            continue;
        }

        if (instructions[target_iterator].first.first == "acc") {
            accumulator += instructions[target_iterator].first.second;
            instructions[target_iterator].second = true;
            target_iterator++;
            continue;
        }
        
        if (instructions[target_iterator].first.first == "jmp") {
            if (!is_changed && changed_positions.find(target_iterator) == changed_positions.end()) {
                instructions[target_iterator].second = true;
                changed_positions.emplace(target_iterator, true);
                target_iterator++;
                is_changed = true;
                continue;
            }

            instructions[target_iterator].second = true;
            target_iterator += instructions[target_iterator].first.second;
            continue;
        }

        if (instructions[target_iterator].first.first == "nop") {
            if (!is_changed && changed_positions.find(target_iterator) == changed_positions.end()) {
                instructions[target_iterator].second = true;
                changed_positions.emplace(target_iterator, true);
                target_iterator += instructions[target_iterator].first.second;
                is_changed = true;
                continue;
            }

            instructions[target_iterator].second = true;
            target_iterator++;
            continue;
        }

        break;
    }

    std::cout << "Accumulator: " << accumulator << std::endl;

    return 0;
}