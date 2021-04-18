#include <cmath>
#include <array>
#include <vector>
#include <fstream>
#include <iostream>

int main() {
    std::ifstream ifs("day12_input.txt");
    if (!ifs) {
        std::cout << "Failed to open the input file." << std::endl;
        return -1;
    }

    std::string read_line;
    std::vector<std::pair<std::string, int>> directions;
    while (!ifs.eof()) {
        std::getline(ifs, read_line);

        directions.emplace_back(
            std::make_pair(read_line.substr(0, 1), std::stoi(read_line.substr(1, read_line.length() - 1))));
    }

    std::pair<int, int> now_position = std::make_pair( 0, 0);  // <E/W distance, N/S distance>
    std::pair<int, int> now_waypoint = std::make_pair(10, 1);  // <E/W units, N/S units>
    for (const auto& direction : directions) {
        if (direction.first == "N") {
            now_waypoint.second += direction.second;
            continue;
        }

        if (direction.first == "S") {
            now_waypoint.second -= direction.second;
            continue;
        }

        if (direction.first == "E") {
            now_waypoint.first += direction.second;
            continue;
        }

        if (direction.first == "W") {
            now_waypoint.first -= direction.second;
            continue;
        }

        if (direction.first == "F") {
            now_position.first  += now_waypoint.first  * direction.second;
            now_position.second += now_waypoint.second * direction.second;
            continue;
        }

        if ((direction.first == "R" && direction.second ==  90) ||
            (direction.first == "L" && direction.second == 270)) {
            now_waypoint = std::make_pair(now_waypoint.second, now_waypoint.first * -1);
            continue;
        }

        if ((direction.first == "R" && direction.second == 180) ||
            (direction.first == "L" && direction.second == 180)) {
            now_waypoint = std::make_pair(now_waypoint.first * -1, now_waypoint.second * -1);
            continue;
        }

        if ((direction.first == "R" && direction.second == 270) ||
            (direction.first == "L" && direction.second ==  90)) {
            now_waypoint = std::make_pair(now_waypoint.second * -1, now_waypoint.first);
            continue;
        }
    }

    std::cout << "Manhattan distance: "
              << std::abs(now_position.first) + std::abs(now_position.second)
              << std::endl;
}