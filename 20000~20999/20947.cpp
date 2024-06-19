#include <algorithm>
#include <iostream>
#include <limits>
#include <numeric>
#include <vector>

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    int N;
    std::cin >> N;

    std::vector<std::vector<char>> board(N, std::vector<char>(N));
    for (auto& row : board)
        for (auto& cell : row) std::cin >> cell;

    std::vector<std::vector<bool>> is_safe(N, std::vector<bool>(N, false));
    for (int i = 0; i < N; ++i)
        for (int j = 0; j < N; ++j)
            if (board[i][j] == 'O') {
                int dx[] = {0, 0, 1, -1};
                int dy[] = {1, -1, 0, 0};

                for (int k = 0; k < 4; ++k) {
                    int x = i + dx[k];
                    int y = j + dy[k];

                    while (0 <= x && x < N && 0 <= y && y < N &&
                           board[x][y] == '.') {
                        is_safe[x][y] = true;
                        x += dx[k];
                        y += dy[k];
                    }
                }
            }

    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j)
            if (board[i][j] == '.')
                std::cout << (is_safe[i][j] ? '.' : 'B');
            else
                std::cout << board[i][j];
        std::cout << '\n';
    }

    return 0;
}
