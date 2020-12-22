#include <vector>
#include <fstream>
#include <iostream>
#include <unordered_map>

int main() {
    std::ifstream ifs("day11_input.txt");
    if (!ifs) {
        std::cout << "Failed to open the input file." << std::endl;
        return -1;
    }

    int rows_count { 0 };
    int columns_count { 0 };
    std::string read_line;
    std::vector<char> rows;
    std::vector<std::vector<char>> seats;
    while (!ifs.eof()) {
        std::getline(ifs, read_line);

        if (columns_count == 0) {
            columns_count = read_line.length();
        }

        for (const auto& seat: read_line) {
            rows.emplace_back(seat);
        }
        seats.emplace_back(rows);
        std::vector<char>().swap(rows);
        rows_count++;
    }

    int occupied_seats_count    { 0 };
    bool is_seat_state_changed { true };
    std::vector<std::vector<char>> tmp_seats;
    std::unordered_map<char, char> opposite_state{{'L', '#'}, {'#', 'L'}};
    while (true) {
        for (int i = 0; i < rows_count; i++) {
            std::vector<char> rows;
            for (int j = 0; j < columns_count; j++) {
                if (seats[i][j] == '.') {
                    rows.emplace_back(seats[i][j]);
                    continue;
                }

                int occupied_adjacent_seats = 0; 
                char now_state = seats[i][j];
                if (0 <= (i - 1)) {
                    if (seats[i - 1][j] == '#') occupied_adjacent_seats++;
                    if (0 <= (j - 1)) {
                        if (seats[i - 1][j - 1] == '#') occupied_adjacent_seats++;
                    }
                    if (j + 1 <= columns_count) {
                        if (seats[i - 1][j + 1] == '#') occupied_adjacent_seats++;
                    }
                }

                if (i + 1 <= rows_count - 1) {
                    if (seats[i + 1][j] == '#') occupied_adjacent_seats++;
                    if (0 <= (j - 1)) {
                        if (seats[i + 1][j - 1] == '#') occupied_adjacent_seats++;
                    }
                    if (j + 1 <= columns_count) {
                        if (seats[i + 1][j + 1] == '#') occupied_adjacent_seats++;
                    }
                }

                if (0 <= j - 1) {
                    if (seats[i][j - 1] == '#') occupied_adjacent_seats++;
                }

                if (j + 1 <= columns_count - 1) {
                    if (seats[i][j + 1] == '#') occupied_adjacent_seats++;
                }

                if (now_state == 'L' && 0 == occupied_adjacent_seats) {
                    rows.emplace_back(opposite_state[now_state]);
                } else if (now_state == '#' && 4 <= occupied_adjacent_seats) {
                    rows.emplace_back(opposite_state[now_state]);
                } else {
                    rows.emplace_back(now_state);
                }

                occupied_adjacent_seats = 0;
            }

            tmp_seats.emplace_back(rows);
            std::vector<char>().swap(rows);
        }

        seats.swap(tmp_seats);

        if (seats == tmp_seats) {
            is_seat_state_changed = false;
            break;
        }

        std::vector<std::vector<char>>().swap(tmp_seats);
    }

    for (const auto& row : seats) {
        for (const auto& seat : row) {
            if (seat == '#') {
                occupied_seats_count++;
            }
        }
    }

    std::cout << "Occupied Seats Count: " << occupied_seats_count << std::endl;
}