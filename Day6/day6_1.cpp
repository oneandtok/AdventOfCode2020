#include <fstream>
#include <iostream>
#include <unordered_map>

int main() {
    std::ifstream ifs("day6_input.txt");
    if (!ifs) {
        std::cout << "Failed to open input file." << std::endl;
        return -1;
    }

    int total_answered_qustions { 0 };
    std::string read_line;
    std::unordered_map<char, bool> question_list;

    while(!ifs.eof()) {
        std::getline(ifs, read_line);

        if (read_line.empty()) {
            // 読み込んだ行が空白行のとき
            total_answered_qustions += question_list.size();

            // question_listをリセット
            question_list.clear();
        }

        // 空白行でないとき、その行の一文字ずつをunordered_mapへtry_emplace
        for (const auto& ch : read_line) {
            question_list.try_emplace(ch, true);
        }
    }

    // 最終グループの回答の集計
    total_answered_qustions += question_list.size();

    std::cout << "Total Answered Questions: " << total_answered_qustions << std::endl;
}