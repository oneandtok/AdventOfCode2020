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
    int read_lines { 0 };  // read_lines == count of people who answered more than one question
    std::string read_line;
    std::unordered_map<char, int> question_list;  // unordered_map<question_index, answered_count_in_the_group>

    while(!ifs.eof()) {
        std::getline(ifs, read_line);

        if (read_line.empty()) {
            // 読み込んだ行が空白行のとき
            for (const auto& question : question_list) {
                if (question.second == read_lines) {
                    // そのquetionに対する回答数が、グループ内で1つ以上何らかの質問に"yes"と回答した人数と一致するとき
                    total_answered_qustions++;
                }
            }

            // question_list, read_linesをリセット
            question_list.clear();
            read_lines = 0;

            continue;
        }

        // 空白行でないとき、その行の一文字ずつをunordered_mapへtry_emplace
        for (const auto& ch : read_line) {
            if (question_list.count(ch) == 0) {
                // キー(既にグループ内で回答された質問)が存在しないとき、unordered_mapにキーと回答数"1"を追加
                question_list.emplace(ch, 1);
            } else {
                // キーが既に存在しているとき、既に格納されている回答数に1を追加して代入
                question_list.insert_or_assign(ch, question_list[ch] + 1);
            }
        }
        read_lines++;
    }

    // 最終グループの回答の集計
    for (const auto& question : question_list) {
        if (question.second == read_lines) {
            // そのquetionに対する回答数が、グループ内で1つ以上何らかの質問に"yes"と回答した人数と一致するとき
            total_answered_qustions++;
        }
    }

    std::cout << "Total Answered Questions: " << total_answered_qustions << std::endl;
}