#include <fstream>
#include <iostream>

int main() {
    std::ifstream ifs("day4_input.txt");

    int valid_passport_count { 0 };
    bool byr { false };
    bool iyr { false };
    bool eyr { false };
    bool hgt { false };
    bool hcl { false };
    bool ecl { false };
    bool pid { false };
    std::string read_line;

    while (!ifs.eof()) {
        std::getline(ifs, read_line);

        if (read_line.empty()) {
            // 空白行のとき
            if (byr && iyr && eyr && hgt && hcl && ecl && pid) {
                // 直前のパスポートの有効性検証
                valid_passport_count++;
            }

            // 必須7項目のbool値を初期化し、次のパスポートの検証へ
            byr = iyr = eyr = hgt = hcl = ecl = pid = false;
            continue;
        }

        if (read_line.find("byr:") != std::string::npos) {
            byr = true;
        }
        if (read_line.find("iyr:") != std::string::npos) {
            iyr = true;
        }
        if (read_line.find("eyr:") != std::string::npos) {
            eyr = true;
        }
        if (read_line.find("hgt:") != std::string::npos) {
            hgt = true;
        }
        if (read_line.find("hcl:") != std::string::npos) {
            hcl = true;
        }
        if (read_line.find("ecl:") != std::string::npos) {
            ecl = true;
        }
        if (read_line.find("pid:") != std::string::npos) {
            pid = true;
        }
    }

    // 最終のパスポートの有効性検証
    if (byr && iyr && eyr && hgt && hcl && ecl && pid) {
        valid_passport_count++;
    }

    std::cout << "Count of Valid Passport: " << valid_passport_count << std::endl;
}