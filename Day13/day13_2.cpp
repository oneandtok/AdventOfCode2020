#include <vector>
#include <fstream>
#include <iostream>

inline int64_t mod(int64_t a, int64_t b) {
    return (a % b + b) % b;
}

int64_t extGcd(int64_t a, int64_t b, int64_t& p, int64_t& q) {
    if (b == 0) {
        p = 1;
        q = 0;
        return a;
    }

    int64_t d = extGcd(b, a % b, q, p);
    q -= a / b * p;
    return d;
}

std::pair<int64_t, int64_t> ChineseRem(int64_t b1, int64_t m1, int64_t b2, int64_t m2) {
    int64_t p, q;
    int64_t d = extGcd(m1, m2, p, q);
    if ((b2 - b1) % d != 0) {
        return std::make_pair(0, -1);
    }

    int64_t m = m1 * (m2 / d) * p % (m2 / d);
    int64_t tmp = (b2 - b1) / d * p % (m2 / d);
    int64_t r = mod(b1 + m1 * tmp, m);

    return std::make_pair(r, m);
}

int main() {
    std::ifstream ifs("day13_input.txt");
    if (!ifs) {
        std::cout << "Failed to open the input file." << std::endl;
        return -1;
    }

    bool is_reading_first_line { true };
    int earliest_timestamp;
    int64_t minutes_after_first_id { -1 };
    std::string read_line;
    std::string bus_id;
    std::vector<std::pair<int64_t, int64_t>> bus_ids;
    while (!ifs.eof()) {
        std::getline(ifs, read_line);

        if (is_reading_first_line) {
            is_reading_first_line = false;
            continue;
        }

        for (const auto& char_int : read_line) {
            if (char_int == 'x') {
                minutes_after_first_id++;
                continue;
            }

            if (char_int == ',') {
                if (bus_id.empty()) continue;

                bus_ids.emplace_back(std::make_pair(std::stoll(bus_id) * -1, minutes_after_first_id));
                bus_id.clear();
                continue;
            }

            if (bus_id.empty()) {
                minutes_after_first_id++;
            }
            bus_id += char_int;
        }
    }

    bus_ids.emplace_back(std::make_pair(std::stoll(bus_id) * -1, minutes_after_first_id));

    std::sort(bus_ids.begin(), bus_ids.end());
    for (auto& bus_id_and_time : bus_ids) {
        bus_id_and_time.first = bus_id_and_time.first * -1;
    }
    for (auto& bus_id_and_time : bus_ids) {
        std::cout << "[" << bus_id_and_time.first << ", " << bus_id_and_time.second << "]" << std::endl;
    }

    std::pair<int64_t, int64_t> ret =
        ChineseRem(bus_ids[0].first, bus_ids[0].second, bus_ids[1].first, bus_ids[1].second);

    for (int i = 2; i < bus_ids.size(); i++) {
        std::cout << __LINE__ << std::endl;
        ret = ChineseRem(ret.first, ret.second, bus_ids[i].first, bus_ids[i].second);
    }

    std::cout << "x: " << ret.first << "mod: " << ret.second << std::endl;
}
