#include <algorithm>
#include <iostream>
#include <limits>
#include <numeric>
#include <vector>

int getCrossLength(int x, int y, int N, int M,
                   const std::vector<std::vector<char>>& board) {
    int length = 0;
    while (0 <= x - length && x + length < N && 0 <= y - length &&
           y + length < M)
        if (board[x - length][y] == '#' && board[x + length][y] == '#' &&
            board[x][y - length] == '#' && board[x][y + length] == '#')
            ++length;
        else
            break;

    return length - 1;
}

void placeCross(int x, int y, int length,
                std::vector<std::vector<char>>& board) {
    for (int i = 0; i <= length; ++i) {
        board[x - i][y] = '+';
        board[x + i][y] = '+';
        board[x][y - i] = '+';
        board[x][y + i] = '+';
    }
}

void undoCross(int x, int y, int length,
               std::vector<std::vector<char>>& board) {
    for (int i = 0; i <= length; ++i) {
        board[x - i][y] = '#';
        board[x + i][y] = '#';
        board[x][y - i] = '#';
        board[x][y + i] = '#';
    }
}

int getCrossArea(int length) { return 1 + 4 * length; }

int backtrack(int idx, bool isPlaced, int N, int M,
              std::vector<std::vector<char>>& board) {
    if (idx == N * M) return -1;

    int x = idx / M;
    int y = idx % M;

    if (isPlaced) {
        if (board[x][y] == '#')
            return std::max(getCrossLength(x, y, N, M, board),
                            backtrack(idx + 1, true, N, M, board));
        else
            return backtrack(idx + 1, true, N, M, board);
    }

    int maxProduct = backtrack(idx + 1, false, N, M, board);

    if (board[x][y] == '#') {
        int length = getCrossLength(x, y, N, M, board);

        for (int i = 0; i <= length; ++i) {
            placeCross(x, y, i, board);
            int curProduct = getCrossArea(i) * getCrossArea(backtrack(
                                                   idx + 1, true, N, M, board));
            undoCross(x, y, i, board);

            maxProduct = std::max(maxProduct, curProduct);
        }
    }

    return maxProduct;
}

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    int N, M;
    std::cin >> N >> M;

    std::vector<std::vector<char>> board(N, std::vector<char>(M));
    for (auto& row : board)
        for (auto& cell : row) std::cin >> cell;

    std::cout << backtrack(0, false, N, M, board) << '\n';

    return 0;
}