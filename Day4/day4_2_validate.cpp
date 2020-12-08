#include "day4_2_validate.h"

#include <cctype>
#include <vector>
#include <fstream>
#include <unordered_map>

// Global Variables
extern bool byr;
extern bool iyr;
extern bool eyr;
extern bool hgt;
extern bool hcl;
extern bool ecl;
extern bool pid;

bool Xdigits_Check (const std::string& subject) {
    if (std::count_if(subject.begin(), subject.end(),
            [](unsigned char c) {
                return std::isxdigit(c);
            }) == 6) {
        // std::cout << "Xdigits_Check: TRUE" << std::endl;
        return true;
    }

    return false;
}

void CheckByr(const std::string& byr_str) {
    if (byr_str.length() != 4) return;

    try {
        if (1920 <= std::stoi(byr_str) && std::stoi(byr_str) <= 2002) {
            // std::cout << "CheckByr: TRUE" << std::endl;
            byr = true;
            return;
        } else {
            return;
        }
    } catch (...) {
        return;
    }
}

void CheckIyr(const std::string& iyr_str) {
    if (iyr_str.length() != 4) return;

    try {
        if (2010 <= std::stoi(iyr_str) && std::stoi(iyr_str) <= 2020) {
            // std::cout << "CheckIyr: TRUE" << std::endl;
            iyr = true;
            return;
        } else {
            return;
        }
    } catch (...) {
        return;
    }
}

void CheckEyr(const std::string& eyr_str) {
    if (eyr_str.length() != 4) return;
    try {
        if (2020 <= std::stoi(eyr_str) && std::stoi(eyr_str) <= 2030) {
            // std::cout << "CheckEyr: TRUE" << std::endl;
            eyr = true;
            return;
        } else {
            return;
        }
    } catch (...) {
        return;
    }
}

void CheckHgt(const std::string& hgt_str) {
    if (hgt_str.find("cm") != std::string::npos) {
        try {
            if (150 <= std::stoi(hgt_str.substr(0, hgt_str.find("cm"))) &&
                    std::stoi(hgt_str.substr(0, hgt_str.find("cm"))) <= 193) {
                // std::cout << "CheckHgt: TRUE" << std::endl;
                hgt = true;
                return;
            }
        } catch (...) {
            return;
        }
    } else if (hgt_str.find("in") != std::string::npos) {
        try {
            if (59 <= std::stoi(hgt_str.substr(0, hgt_str.find("in"))) &&
                    std::stoi(hgt_str.substr(0, hgt_str.find("in"))) <= 76) {
                // std::cout << "CheckHgt: TRUE" << std::endl;
                hgt = true;
                return;
            }
        } catch (...) {
            return;
        }
    } else {
        return;
    }
}

void CheckHcl(const std::string& hcl_str) {
    if (hcl_str.length() != 7) return;
    if (hcl_str.find("#") == std::string::npos || hcl_str.find("#") != 0) return ;
    if (Xdigits_Check(hcl_str.substr(1, 6))) {
        // std::cout << "CheckHcl: TRUE" << std::endl;
        hcl = true;
        return;
    }

    return;
}

void CheckEcl(const std::string& ecl_str) {
    if (ecl_str == "amb" || ecl_str == "blu" || ecl_str == "brn" ||
            ecl_str == "gry" || ecl_str == "grn" || ecl_str == "hzl" ||
            ecl_str == "oth") {
        // std::cout << "CheckEcl: TRUE" << std::endl;
        ecl = true;
        return;
    }

    return;
}

void CheckPid(const std::string& pid_str) {
    if (pid_str.length() != 9) {
        return;
    }

    // std::cout << "CheckPid: TRUE" << std::endl;
    pid = true;
    return;
}
