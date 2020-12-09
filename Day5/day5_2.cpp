#include <cmath>
#include <vector>
#include <fstream>
#include <iostream>
#include <algorithm>

int ConvertCharToInt(const std::string& value) {
    if (value == "F") return 0;
    if (value == "B") return 1;
    if (value == "R") return 1;
    if (value == "L") return 0;

    return -1;
}

int CalcSeatId(const std::string& pass) {
    std::string row_str    = pass.substr(0, 7);
    std::string column_str = pass.substr(7, 3);

    // row
    int row = std::pow(2, 6) * ConvertCharToInt(row_str.substr(0, 1)) +
                std::pow(2, 5) * ConvertCharToInt(row_str.substr(1, 1)) +
                std::pow(2, 4) * ConvertCharToInt(row_str.substr(2, 1)) +
                std::pow(2, 3) * ConvertCharToInt(row_str.substr(3, 1)) +
                std::pow(2, 2) * ConvertCharToInt(row_str.substr(4, 1)) +
                std::pow(2, 1) * ConvertCharToInt(row_str.substr(5, 1)) +
                std::pow(2, 0) * ConvertCharToInt(row_str.substr(6, 1));

    // column
    int column = std::pow(2, 2) * ConvertCharToInt(column_str.substr(0, 1)) +
                    std::pow(2, 1) * ConvertCharToInt(column_str.substr(1, 1)) +
                    std::pow(2, 0) * ConvertCharToInt(column_str.substr(2, 1));

    return row * 8 + column;
}


int main() {
    std::ifstream ifs("day5_input.txt");
    if (!ifs) {
        std::cout << "Failed to open input file." << std::endl;
        return -1;
    }

    int min_seat_id_minus_one = CalcSeatId("FFFFFFFRRR");
    int max_seat_id_plus_one  = CalcSeatId("BBBBBBBLLL");
    std::string read_line;
    std::vector<int> seat_ids;

    while (!ifs.eof()) {
        std::getline(ifs, read_line);

        int seat_id = CalcSeatId(read_line);
        if (min_seat_id_minus_one < seat_id && seat_id <max_seat_id_plus_one) {
            seat_ids.emplace_back(seat_id);
        }
    }

    int previous_seat_id { 0 };
    int next_seat_id { 0 };
    std::sort(seat_ids.begin(), seat_ids.end());
    for (const auto& seat_id : seat_ids) {
        previous_seat_id = next_seat_id;
        next_seat_id = seat_id;

        if (min_seat_id_minus_one < previous_seat_id && (next_seat_id - previous_seat_id) != 1) {
            std::cout << "My Seat ID: " << previous_seat_id + 1 << std::endl;
            break;
        }
    }

    return 0;
}