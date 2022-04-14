#include <algorithm>
#include <iostream>
#include <vector>

void backtrack(unsigned cell, std::vector<std::vector<unsigned>>& board,
               std::vector<std::vector<bool>>& vertical,
               std::vector<std::vector<bool>>& horizontal,
               std::vector<std::vector<bool>>& square, bool& solved) {
    if (cell == 81) {
        solved = true;
        return;
    }

    unsigned i = cell / 9;
    unsigned j = cell % 9;

    if (board[i][j]) {
        backtrack(cell + 1, board, vertical, horizontal, square, solved);
        return;
    }

    for (unsigned k = 1; k <= 9 && !solved; ++k) {
        if (!vertical[j][k - 1] || !horizontal[i][k - 1] ||
            !square[i / 3 * 3 + j / 3][k - 1])
            continue;

        board[i][j] = k;
        vertical[j][k - 1] = horizontal[i][k - 1] =
            square[i / 3 * 3 + j / 3][k - 1] = false;
        backtrack(cell + 1, board, vertical, horizontal, square, solved);
        vertical[j][k - 1] = horizontal[i][k - 1] =
            square[i / 3 * 3 + j / 3][k - 1] = true;
    }

    if (!solved)
        board[i][j] = 0;

    return;
}

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    std::vector<std::vector<bool>> vertical(9, std::vector<bool>(9, true));
    std::vector<std::vector<bool>> horizontal(9, std::vector<bool>(9, true));
    std::vector<std::vector<bool>> square(9, std::vector<bool>(9, true));

    std::vector<std::vector<unsigned>> board(9, std::vector<unsigned>(9));
    for (int i = 0; i < 9; ++i)
        for (int j = 0; j < 9; ++j) {
            int x;
            std::cin >> x;
            board[i][j] = x;

            if (x) {
                vertical[j][x - 1] = false;
                horizontal[i][x - 1] = false;
                square[i / 3 * 3 + j / 3][x - 1] = false;
            }
        }

    bool solved = false;
    backtrack(0, board, vertical, horizontal, square, solved);
    for (auto i : board) {
        for (auto j : i) std::cout << j << ' ';
        std::cout << '\n';
    }

    return 0;
}
