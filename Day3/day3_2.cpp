#include <fstream>
#include <iostream>

long CountTrees(int right_count, int down_count) {
    std::ifstream ifs("day3_input.txt");
    if (!ifs) {
        std::cout << "Failed to open the input file." << std::endl;
        return 0;
    }

    int  line_count { 1 };
    int  previous_read_line { 1 };
    int  horizontal_position { 0 };
    long encount_trees_count { 0 };
    std::string read_line;
    while (!ifs.eof()) {
        std::getline(ifs, read_line);

        if (read_line.length() < horizontal_position + 1) {
            // horizontal_positionが1行の文字数を超えたら、読み込み開始位置を修正
            horizontal_position = horizontal_position - read_line.length();
        }

        if (down_count != 1) {
            if ((line_count - previous_read_line) != down_count) {
                // 現在読んでいる行数が読み込み対象行まで下がっていないとき
                if (line_count == 1) {
                    // 初回のみhorizontal_positionを指定数進める
                    horizontal_position += right_count;
                }
                // line_countをインクリメントして次の行へ
                line_count++;
                continue;
            } else {
                // 読み込み対象行まで下がったとき
                // previous_read_lineに現在読んでいる行数をセットする
                previous_read_line = line_count;
            }
        }

        if (read_line.substr(horizontal_position, 1) == "#") {
            // 座標(__LINE__, horizontal_position)が"#"のとき
            encount_trees_count++;
        }

        horizontal_position += right_count;
        line_count++;
    }

    return encount_trees_count;
}

int main() {
    long multiplied_answer = CountTrees(1, 1) * 
                             CountTrees(3, 1) *
                             CountTrees(5, 1) *
                             CountTrees(7, 1) *
                             CountTrees(1, 2);

    std::cout << "Multiplied Answer: " << multiplied_answer << std::endl;

    return 0;
}