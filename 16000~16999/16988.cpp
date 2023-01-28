#include <algorithm>
#include <iostream>
#include <limits>
#include <numeric>
#include <queue>
#include <vector>

int countBoard(const std::vector<std::vector<int>>& board, const int N,
               const int M) {
    std::queue<std::pair<int, int>> q;
    std::vector<std::vector<bool>> visited(N, std::vector<bool>(M, false));

    for (int i = 0; i < N; ++i)
        for (int j = 0; j < M; ++j)
            if (board[i][j] == 0) {
                q.push({i, j});
                visited[i][j] = true;
            }

    int dx[] = {0, 0, 1, -1};
    int dy[] = {1, -1, 0, 0};

    while (!q.empty()) {
        const auto [r, c] = q.front();
        q.pop();

        for (int i = 0; i < 4; ++i) {
            int nx = r + dx[i];
            int ny = c + dy[i];

            if (nx < 0 || nx >= N || ny < 0 || ny >= M || visited[nx][ny] ||
                board[nx][ny] == 1)
                continue;

            q.push({nx, ny});
            visited[nx][ny] = true;
        }
    }

    int count = 0;
    for (int i = 0; i < N; ++i)
        for (int j = 0; j < M; ++j)
            if (!visited[i][j] && board[i][j] == 2) ++count;

    return count;
}

int backtrack(std::vector<std::vector<int>>& board, const int N, const int M) {
    int maxCatch = 0;

    for (int i = 0; i < N * M; ++i) {
        const int r1 = i / M;
        const int c1 = i % M;
        if (board[r1][c1] != 0) continue;

        board[r1][c1] = 1;
        for (int j = i + 1; j < N * M; ++j) {
            const int r2 = j / M;
            const int c2 = j % M;
            if (board[r2][c2] != 0) continue;

            board[r2][c2] = 1;
            maxCatch = std::max(maxCatch, countBoard(board, N, M));
            board[r2][c2] = 0;
        }
        board[r1][c1] = 0;
    }

    return maxCatch;
}

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    int N, M;
    std::cin >> N >> M;

    std::vector<std::vector<int>> board(N, std::vector<int>(M));
    for (auto& row : board)
        for (auto& cell : row) std::cin >> cell;

    std::cout << backtrack(board, N, M) << '\n';

    return 0;
}