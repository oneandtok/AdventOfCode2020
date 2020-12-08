#include "day4_2_validate.h"

#include <vector>
#include <fstream>
#include <iostream>
#include <unordered_map>

// Global Variables
bool byr { false };
bool iyr { false };
bool eyr { false };
bool hgt { false };
bool hcl { false };
bool ecl { false };
bool pid { false };

int main() {
    std::ifstream ifs("day4_input.txt");

    int valid_passport_count { 0 };
    std::string read_line;

    // unordered_map<validation_index, validation_item>
    std::unordered_map<std::string, std::string> validation_data;


    while (!ifs.eof()) {
        std::getline(ifs, read_line);

        if (read_line.empty()) {
            // 空白行のとき
            for (const auto& item : validation_data) {
                if (item.first == "byr") {
                    // std::cout << "[" << item.first << ", " << item.second << "]" << std::endl;
                    CheckByr(item.second);
                }
                if (item.first == "iyr") {
                    // std::cout << "[" << item.first << ", " << item.second << "]" << std::endl;
                    CheckIyr(item.second);
                }
                if (item.first == "eyr") {
                    // std::cout << "[" << item.first << ", " << item.second << "]" << std::endl;
                    CheckEyr(item.second);
                }
                if (item.first == "hgt") {
                    // std::cout << "[" << item.first << ", " << item.second << "]" << std::endl;
                    CheckHgt(item.second);
                }
                if (item.first == "hcl") {
                    // std::cout << "[" << item.first << ", " << item.second << "]" << std::endl;
                    CheckHcl(item.second);
                }
                if (item.first == "ecl") {
                    // std::cout << "[" << item.first << ", " << item.second << "]" << std::endl;
                    CheckEcl(item.second);
                }
                if (item.first == "pid") {
                    // std::cout << "[" << item.first << ", " << item.second << "]" << std::endl;
                    CheckPid(item.second);
                }
            }
            // std::cout << std::endl;

            if (byr && iyr && eyr && hgt && hcl && ecl && pid) {
                // 直前のパスポートの有効性検証
                valid_passport_count++;
            }

            // 必須7項目のbool値とunordered_mapを初期化し、次のパスポートの検証へ
            byr = iyr = eyr = hgt = hcl = ecl = pid = false;
            validation_data.clear();
            continue;
        }

        // 1行に含まれる要素は最大8項目 == スペースは最大7個
        int space_count = std::count(read_line.begin(), read_line.end(), ' ');

        if (space_count == 0) {
            // スペースが行に含まれないとき、1要素をunordered_mapに詰めて次の行へ
            validation_data.emplace(read_line.substr(0, 3), read_line.substr(4, read_line.length() - 4));
            continue;
        }

        for (int i = 0; i < space_count + 1; i++) {
            int space_position = read_line.find_first_of(" ");
            if (space_position != std::string::npos) {
                validation_data.emplace(read_line.substr(0, 3), read_line.substr(4, space_position - 4));
            } else {
                validation_data.emplace(read_line.substr(0, 3), read_line.substr(4, read_line.length() - 4));
            }
            read_line = read_line.substr(space_position + 1, read_line.length() - space_position - 1);
        }

    }

    // 最終のパスポートの有効性検証
    for (const auto& item : validation_data) {
        if (item.first == "byr") {
            // std::cout << "[" << item.first << ", " << item.second << "]" << std::endl;
            CheckByr(item.second);
        }
        if (item.first == "iyr") {
            // std::cout << "[" << item.first << ", " << item.second << "]" << std::endl;
            CheckIyr(item.second);
        }
        if (item.first == "eyr") {
            // std::cout << "[" << item.first << ", " << item.second << "]" << std::endl;
            CheckEyr(item.second);
        }
        if (item.first == "hgt") {
            // std::cout << "[" << item.first << ", " << item.second << "]" << std::endl;
            CheckHgt(item.second);
        }
        if (item.first == "hcl") {
            // std::cout << "[" << item.first << ", " << item.second << "]" << std::endl;
            CheckHcl(item.second);
        }
        if (item.first == "ecl") {
            // std::cout << "[" << item.first << ", " << item.second << "]" << std::endl;
            CheckEcl(item.second);
        }
        if (item.first == "pid") {
            // std::cout << "[" << item.first << ", " << item.second << "]" << std::endl;
            CheckPid(item.second);
        }
    }

    if (byr && iyr && eyr && hgt && hcl && ecl && pid) {
        valid_passport_count++;
    }

    std::cout << "Count of Valid Passport: " << valid_passport_count << std::endl;
}