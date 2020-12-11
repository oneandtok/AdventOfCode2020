#include <map>
#include <cctype>
#include <vector>
#include <fstream>
#include <iostream>

int main() {
    std::ifstream ifs("day7_input.txt");
    if (!ifs) {
        std::cout << "Failed to open input file." << std::endl;
        return -1;
    }

    int reading_line { 0 };
    std::string read_line;
    std::multimap<std::string, std::string> colors;

    // 1行ごとにバッグのカラーと内包できるカラーと数量をvector<vector<string>> colorsへ代入
    while (!ifs.eof()) {
        std::getline(ifs, read_line);

        std::string word {};
        std::vector<std::string> words;

        // 行中の各単語をwordsへ格納
        for (const auto& ch : read_line) {
            if (ch != ' ' && ch != ',' && ch != '.') {
                word += ch;
                continue;
            }

            words.emplace_back(word);
            word.clear();
        }

        // wordsを格納し、カラーと数量とでcolorsへ格納
        bool is_first_word  { true };
        bool is_second_word { false };
        std::string essential_item;
        std::string essential_index;
        for (const auto& word : words) {
            if (word.find("no")      != std::string::npos) break;
            if (word.find("contain") != std::string::npos) continue;
            if (word.find("bag")     != std::string::npos) {
                if (!essential_item.empty()) {
                    colors.emplace(essential_index, essential_item.substr(0, essential_item.find_last_of(" ")));
                    essential_item.clear();
                }
                continue;
            }

            if (is_first_word) {
                essential_item += word;
                essential_item += " ";
                is_first_word  = false;
                is_second_word = true;
                continue;
            }

            if (is_second_word) {
                essential_item += word;
                essential_index = essential_item;
                essential_item.clear();
                is_second_word = false;
                continue;
            }

            essential_item += word;
            essential_item += " ";
        }

        word.clear();
        reading_line++;
    }

    // colorsを展開しshiny goldを内包できるバッグをカウント
    std::vector<std::string> targets;
    targets.emplace_back("shiny gold");

    for (const auto& target : targets) {
        for (const auto& color : colors) {
            if (color.second.find(target) != std::string::npos) {
                targets.emplace_back(color.first);
            }
        }
    }

    std::sort(targets.begin(), targets.end());
    targets.erase(std::unique(targets.begin(), targets.end()), targets.end());

    for (const auto& tmp : targets) {
        std::cout << "[" << tmp << "]" << std::endl;
    }

    std::cout << "Total colors, able to contain the target color: "
              << targets.size()
              << std::endl;

    return 0;
}