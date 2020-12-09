#include <cmath>
#include <fstream>
#include <iostream>

int ConvertCharToInt(const std::string& value) {
    if (value == "F") return 0;
    if (value == "B") return 1;
    if (value == "R") return 1;
    if (value == "L") return 0;

    return -1;
}


int main() {
    std::ifstream ifs("day5_input.txt");
    if (!ifs) {
        std::cout << "Failed to open input file." << std::endl;
        return -1;
    }

    int max_seat_id { 0 };
    int seat_id;
    std::string read_line;

    while (!ifs.eof()) {
        std::getline(ifs, read_line);
        std::string row_str    = read_line.substr(0, 7);
        std::string column_str = read_line.substr(7, 3);

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

        // seat_id
        seat_id = row * 8 + column;

        if (max_seat_id < seat_id) {
            max_seat_id = seat_id;
        }
    }

    std::cout << "Max Seat Id: " << max_seat_id << std::endl;

    return 0;
}