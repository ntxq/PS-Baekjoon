#include <algorithm>
#include <iostream>
#include <numeric>
#include <vector>

enum Color { Red = 'C', Blue = 'P', Green = 'Z', Yellow = 'Y' };

int longestRow(const std::vector<std::vector<Color>>& board) {
    int max = 0;
    for (const auto& row : board) {
        int curStart = 0;
        int curEnd = 0;
        Color curColor = row[0];

        for (unsigned i = 1; i < row.size(); ++i)
            if (row[i] == curColor) {
                curEnd = i;
            } else {
                max = std::max(max, curEnd - curStart + 1);
                curStart = i;
                curEnd = i;
                curColor = row[i];
            }

        max = std::max(max, curEnd - curStart + 1);
    }

    return max;
}

int longerCol(const std::vector<std::vector<Color>>& board) {
    int max = 0;
    for (unsigned i = 0; i < board[0].size(); ++i) {
        int curStart = 0;
        int curEnd = 0;
        Color curColor = board[0][i];

        for (unsigned j = 1; j < board.size(); ++j)
            if (board[j][i] == curColor) {
                curEnd = j;
            } else {
                max = std::max(max, curEnd - curStart + 1);
                curStart = j;
                curEnd = j;
                curColor = board[j][i];
            }

        max = std::max(max, curEnd - curStart + 1);
    }

    return max;
}

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    int N;
    std::cin >> N;

    std::vector<std::vector<Color>> board(N, std::vector<Color>(N));
    for (auto& row : board)
        for (auto& cell : row) {
            char c;
            std::cin >> c;
            cell = static_cast<Color>(c);
        };

    int max = 0;
    for (int i = 0; i < N; ++i)
        for (int j = 0; j < N; ++j) {
            // Try swap side
            if (j < N - 1 && board[i][j] != board[i][j + 1]) {
                std::swap(board[i][j], board[i][j + 1]);
                max = std::max(max,
                               std::max(longestRow(board), longerCol(board)));
                std::swap(board[i][j], board[i][j + 1]);
            }

            // Try swap down
            if (i < N - 1 && board[i][j] != board[i + 1][j]) {
                std::swap(board[i][j], board[i + 1][j]);
                max = std::max(max,
                               std::max(longestRow(board), longerCol(board)));
                std::swap(board[i][j], board[i + 1][j]);
            }
        }

    std::cout << max << '\n';

    return 0;
}