#include <algorithm>
#include <iostream>
#include <limits>
#include <numeric>
#include <vector>

int backtrack(int x, int y, std::vector<std::vector<bool>>& used,
              const std::vector<std::vector<int>>& board) {
    if (x == board.size()) return 0;
    if (y == board[0].size()) return backtrack(x + 1, 0, used, board);
    if (used[x][y]) return backtrack(x, y + 1, used, board);

    int ret = 0;

    int dx[] = {-1, 1};
    int dy[] = {-1, 1};
    for (int i = 0; i < 2; ++i) {
        for (int j = 0; j < 2; ++j) {
            int nx = x + dx[i];
            int ny = y + dy[j];

            if (0 <= nx && nx < board.size() && 0 <= ny &&
                ny < board[0].size() && !used[nx][y] && !used[x][ny]) {
                used[x][y] = used[nx][y] = used[x][ny] = true;
                ret = std::max(ret, board[x][y] * 2 + board[nx][y] +
                                        board[x][ny] +
                                        backtrack(x, y + 1, used, board));
                used[x][y] = used[nx][y] = used[x][ny] = false;
            }
        }
    }

    return std::max(ret, backtrack(x, y + 1, used, board));
}

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    int N, M;
    std::cin >> N >> M;

    std::vector<std::vector<int>> board(N, std::vector<int>(M));
    for (auto& row : board)
        for (auto& cell : row) std::cin >> cell;

    std::vector<std::vector<bool>> used(N, std::vector<bool>(M));
    std::cout << backtrack(0, 0, used, board) << '\n';

    return 0;
}
