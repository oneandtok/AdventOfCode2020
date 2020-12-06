#include <fstream>
#include <iostream>

int main() {
    std::ifstream ifs("day3_input.txt");
    if (!ifs) {
        std::cout << "Failed to open the input file." << std::endl;
        return 1;
    }

    int line_count { 1 };
    int encount_trees_count { 0 };
    int horizontal_position { 0 };
    std::string read_line;
    while (!ifs.eof()) {
        std::getline(ifs, read_line);
        if (read_line.length() < horizontal_position + 1) {
            // horizontal_positionが1行の文字数を超えたら、読み込み開始位置を修正
            horizontal_position = horizontal_position % 30 - 1;
        }

        if (read_line.substr(horizontal_position, 1) == "#") {
            // 座標(__LINE__, horizontal_position)が"#"のとき
            encount_trees_count++;
        }

        horizontal_position += 3;
        line_count++;
    }

    std::cout << "Count of encounted trees: " << encount_trees_count << std::endl;

    return 0;
}