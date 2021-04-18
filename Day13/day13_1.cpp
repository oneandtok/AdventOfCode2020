#include <vector>
#include <fstream>
#include <iostream>

int main() {
    std::ifstream ifs("day13_input.txt");
    if (!ifs) {
        std::cout << "Failed to open the input file." << std::endl;
        return -1;
    }

    int earliest_timestamp;
    bool is_first_line { true };
    std::string read_line;
    std::string bus_id;
    std::vector<int> bus_ids;
    while (!ifs.eof()) {
        std::getline(ifs, read_line);

        if (is_first_line) {
            earliest_timestamp = std::stoi(read_line);
            is_first_line = false;
            continue;
        }

        for (const auto& char_int : read_line) {
            if (char_int == 'x') continue;
            if (char_int == ',') {
                if (bus_id.empty()) continue;

                bus_ids.emplace_back(std::stoi(bus_id));
                bus_id.clear();
                continue;
            }

            bus_id += char_int;
        }
    }

    std::pair<int, int> bus_id_and_time {0, 999'999'999};
    for (const auto& bus_id : bus_ids) {
        int tmp_timestamp = bus_id * ((earliest_timestamp / bus_id) + 1);
        if (tmp_timestamp < bus_id_and_time.second) {
            bus_id_and_time = std::make_pair(bus_id, tmp_timestamp);
        }
    }

    int multiplied_number = bus_id_and_time.first * (bus_id_and_time.second - earliest_timestamp);

    std::cout << "[bus_id: " << bus_id_and_time.first << ", time: " << bus_id_and_time.second << "]" << std::endl;
    std::cout << "Multiplied the number: " << multiplied_number << std::endl;
}