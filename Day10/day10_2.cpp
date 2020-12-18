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

    jolts.emplace_back(0);
    std::sort(jolts.begin(), jolts.end());
    jolts.emplace_back(jolts.back() + 3);  // my device's built-in adupter

    long long arranges { 1 };
    for (int i = 1; i < jolts.size() - 1; i++) {
        long long patterns { 0 };
        if (jolts[i + 1] - jolts[i - 1] <= 3) {
        std::cout << "[" << jolts[i] << " : 2]" << std::endl;
            patterns = 2;
        } else {
        std::cout << "[" << jolts[i] << " : 1]" << std::endl;
            patterns = 1;
        }

        arranges *= patterns;
        patterns = 0;
    }

    std::cout << "Arrange Count: " << arranges << std::endl;
}