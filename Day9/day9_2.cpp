#include <vector>
#include <fstream>
#include <iostream>

int main() {
    std::ifstream ifs("day9_input.txt");

    if (!ifs) {
        std::cout << "Failed to open the input file." << std::endl;
        return -1;
    }

    std::string read_line;
    std::vector<long long> input_numbers;

    while (!ifs.eof()) {
        std::getline(ifs, read_line);
        input_numbers.emplace_back(std::stoll(read_line));
    }

    int iterator_begin {  0 };
    int iterator_end   { 25 };
    bool found_number { false };
    bool stuck_target { false };
    long long stuck_number;
    std::vector<long long> find_sum_numbers;  // always 25numbers in it
    std::vector<long long> temporary_stock_sum_values;

    while (true) {
        if (stuck_target) break;
        for (int i = 25; i < input_numbers.size(); i++) {
            if (found_number) break;            
            for (int i = iterator_begin; i < iterator_end; i++) {
                find_sum_numbers.emplace_back(input_numbers[i]);
            }

            long long target_number = input_numbers[i];
            for (int i = iterator_begin; i < iterator_end; i++) {
                if (found_number) break;
                for (int j = iterator_begin; j < iterator_end; j++) {
                        if (input_numbers[i] + input_numbers[j] == target_number) {
                            found_number = true;
                            break;
                        }
                }
            }

            if (found_number) {
                iterator_begin++;
                iterator_end++;
                found_number = false;
                continue;
            }

            stuck_target = true;
            stuck_number = target_number;
            break;
        }
    }

    int iterator { 0 };
    long long weakness_number { 0 };
    long long sum_value { 0 };
    std::vector<long long> series_numbers;

    std::cout << "[" << stuck_number << "]" << std::endl;

    while (true) {
        if (weakness_number != 0) break;

        for (int i = iterator; i < input_numbers.size(); i++) {
            if (stuck_number < sum_value) {
                iterator++;
                sum_value = 0;
                series_numbers.clear();
                break;
            }

            if (sum_value == stuck_number) {
                long long min_number { 0 };
                long long max_number { 0 };
                for (const auto& number : series_numbers) {
                    if (min_number == 0) {
                        min_number = number;
                        continue;
                    }

                    if (number < min_number) {
                        min_number = number;
                        continue;
                    }

                    if (max_number < number) {
                        max_number = number;
                        continue;
                    }
                }

                weakness_number = min_number + max_number;
                std::cout << "[iterator: "   << iterator   << "]" << std::endl;
                std::cout << "[min_number: " << min_number << "]" << std::endl;
                std::cout << "[max_number: " << max_number << "]" << std::endl;

                break;
            }

            series_numbers.emplace_back(input_numbers[i]);
            sum_value += input_numbers[i];
        }
    }

    std::cout << "The Weakness Number: " << weakness_number << std::endl;
}