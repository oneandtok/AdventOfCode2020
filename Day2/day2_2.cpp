#include <iostream>
#include <fstream>
#include <vector>
#include <tuple>

int main() {
    // inputファイルをオープン
    std::ifstream ifs("day2_input.txt");
    if (!ifs) {
        std::cout << "Failed to open the input file." << std::endl;
        return 1;
    }

    int first_hyphen;
    int first_space;
    int first_colon;
    std::vector<std::tuple<int, int, std::string, std::string>>  password_options;
    std::string read_line;

    // ファイルの最終行までvector<tuple<minimum_count, max_count, necessary_string, password_option>>に格納
    while (!ifs.eof()) {
        std::getline(ifs, read_line);
        first_hyphen = read_line.find_first_of('-');
        first_space  = read_line.find_first_of(' ');
        first_colon  = read_line.find_first_of(':');

        password_options.emplace_back(std::make_tuple(
                            std::stoi(read_line.substr(0, first_hyphen)),
                            std::stoi(read_line.substr(first_hyphen + 1, first_space - first_hyphen - 1)),
                            read_line.substr(first_space + 1, 1),
                            read_line.substr(first_colon + 2, read_line.length() - first_colon - 1)));
    }

    // vectorに格納したpassword_optionsの有効性検証
    int  string_count;
    int  valid_password_count { 0 };
    std::string password;
    std::string necessary_string;
    for (const auto& password_option : password_options) {
        // passwordの指定位置にnecessary_stringが含まれているか検証
        password         = std::get<3>(password_option);
        necessary_string = std::get<2>(password_option);

        // 条件を満たす場合にvalid_password_countをインクリメント
        if (password.substr(std::get<0>(password_option) - 1, 1) == necessary_string &&
                password.substr(std::get<1>(password_option) - 1, 1) != necessary_string) {
            valid_password_count++;
        } else if (password.substr(std::get<0>(password_option) - 1, 1) != necessary_string &&
                password.substr(std::get<1>(password_option) - 1, 1) == necessary_string) {
            valid_password_count++;
        }
    }

    std::cout << "Count of valid passwords: " << valid_password_count << std::endl;

    return 0;
}