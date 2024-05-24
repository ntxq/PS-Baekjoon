
#include <algorithm>
#include <iostream>
#include <limits>
#include <numeric>
#include <queue>
#include <vector>

int bfs(int m, const std::vector<std::vector<bool>>& board) {
    std::queue<std::pair<int, int>> q;
    std::vector<std::vector<int>> dist(
        2, std::vector<int>(m, std::numeric_limits<int>::max()));

    if (board[0][0]) {
        q.push({0, 0});
        dist[0][0] = 1;
    }
    if (board[1][0]) {
        q.push({1, 0});
        dist[1][0] = 1;
    }

    while (!q.empty()) {
        auto [x, y] = q.front();
        q.pop();

        int dx[] = {0, 0, 1, -1};
        int dy[] = {1, -1, 0, 0};
        for (int i = 0; i < 4; ++i) {
            int nx = x + dx[i];
            int ny = y + dy[i];

            if (0 <= nx && nx < 2 && 0 <= ny && ny < m && board[nx][ny] &&
                dist[nx][ny] == std::numeric_limits<int>::max()) {
                q.push({nx, ny});
                dist[nx][ny] = dist[x][y] + 1;
            }
        }
    }

    return std::min(dist[0][m - 1], dist[1][m - 1]);
}

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    int M;
    std::cin >> M;

    std::vector<std::vector<bool>> board(2, std::vector<bool>(M));
    for (int i = 0; i < 2; ++i)
        for (int j = 0; j < M; ++j) {
            char c;
            std::cin >> c;
            board[i][j] = c == '.';
        }

    int whiteBlocks = std::accumulate(board[0].begin(), board[0].end(), 0) +
                      std::accumulate(board[1].begin(), board[1].end(), 0);
    int minDist = bfs(M, board);

    std::cout << (whiteBlocks - minDist) << '\n';

    return 0;
}
