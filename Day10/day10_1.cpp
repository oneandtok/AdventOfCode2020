#include <vector>
#include <fstream>
#include <iostream>
#include <algorithm>

int main() {
    std::ifstream ifs("day10_input.txt");

    if (!ifs) {
        std::cout << "Failed to open the input file." << std::endl;
        return -1;
    }

    std::string read_line;
    std::vector<int> jolts;

    while (!ifs.eof()) {
        std::getline(ifs, read_line);
        jolts.emplace_back(std::stoi(read_line));
    }

    std::sort(jolts.begin(), jolts.end());
    jolts.emplace_back(jolts.back() + 3);  // my device's built-in adupter

    int one_jolt_diff_count   { 0 };
    int three_jolt_diff_count { 0 };
    int previous_jolt { 0 };
    for (const auto& jolt : jolts) {
        if (jolt - previous_jolt == 1) {
            one_jolt_diff_count++;
            previous_jolt = jolt;
            continue;
        }

        if (jolt - previous_jolt == 3) {
            three_jolt_diff_count++;
            previous_jolt = jolt;
            continue;
        }

        previous_jolt = jolt;
    }

    std::cout << "one_jolt_diff_count: "   << one_jolt_diff_count   << std::endl;
    std::cout << "three_jolt_diff_count: " << three_jolt_diff_count << std::endl;
    std::cout << "Multiplied Numbers: "    << one_jolt_diff_count * three_jolt_diff_count << std::endl;
}