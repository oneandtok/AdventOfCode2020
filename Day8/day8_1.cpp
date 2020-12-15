#include <tuple>
#include <vector>
#include <fstream>
#include <iostream>

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

    while (true) {
        if (instructions[target_iterator].second) break;

        if (instructions[target_iterator].first.first == "acc") {
            accumulator += instructions[target_iterator].first.second;
            instructions[target_iterator].second = true;
            target_iterator++;
            continue;
        }
        
        if (instructions[target_iterator].first.first == "jmp") {
            instructions[target_iterator].second = true;
            target_iterator += instructions[target_iterator].first.second;
            continue;
        }

        if (instructions[target_iterator].first.first == "nop") {
            instructions[target_iterator].second = true;
            target_iterator++;
            continue;
        }

        break;
    }

    std::cout << "Accumulator: " << accumulator << std::endl;

    return 0;

}