#include <algorithm>
#include <array>
#include <iostream>

bool backtrack(std::array<std::array<int, 9>, 9>& board,
               std::array<std::array<bool, 9>, 9>& row,
               std::array<std::array<bool, 9>, 9>& col,
               std::array<std::array<bool, 9>, 9>& box, int x, int y) {
    if (x == 9) return true;
    if (board[x][y])
        return backtrack(board, row, col, box, x + (y + 1) / 9, (y + 1) % 9);

    bool solved = false;
    for (int item = 0; item < 9 && !solved; ++item)
        if (!row[x][item] && !col[y][item] && !box[x / 3 * 3 + y / 3][item]) {
            board[x][y] = item + 1;
            row[x][item] = col[y][item] = box[x / 3 * 3 + y / 3][item] = true;
            solved =
                backtrack(board, row, col, box, x + (y + 1) / 9, (y + 1) % 9);
            if (!solved) {
                row[x][item] = col[y][item] = box[x / 3 * 3 + y / 3][item] =
                    false;
                board[x][y] = 0;
            }
        }

    return solved;
}

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    std::array<std::array<int, 9>, 9> board;

    std::array<std::array<bool, 9>, 9> row{};
    std::array<std::array<bool, 9>, 9> col{};
    std::array<std::array<bool, 9>, 9> box{};

    for (int i = 0; i < 9; ++i)
        for (int j = 0; j < 9; ++j) {
            char c;
            std::cin >> c;
            board[i][j] = c - '0';

            if (board[i][j])
                row[i][board[i][j] - 1] = col[j][board[i][j] - 1] =
                    box[i / 3 * 3 + j / 3][board[i][j] - 1] = true;
        }

    backtrack(board, row, col, box, 0, 0);
    for (const auto& row : board) {
        for (const auto& item : row) std::cout << item;
        std::cout << '\n';
    }

    return 0;
}