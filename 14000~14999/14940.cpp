#include <algorithm>
#include <iostream>
#include <limits>
#include <numeric>
#include <queue>
#include <vector>

std::vector<std::vector<int>> bfs(int sx, int sy,
                                  const std::vector<std::vector<int>>& board) {
    std::vector<std::vector<int>> dist(board.size(),
                                       std::vector<int>(board[0].size(), -1));
    std::queue<std::pair<int, int>> q;

    dist[sx][sy] = 0;
    q.push({sx, sy});

    int dx[] = {0, 0, 1, -1};
    int dy[] = {1, -1, 0, 0};

    while (!q.empty()) {
        auto [x, y] = q.front();
        q.pop();

        for (int i = 0; i < 4; ++i) {
            int nx = x + dx[i];
            int ny = y + dy[i];

            if (0 <= nx && nx < board.size() && 0 <= ny &&
                ny < board[0].size() && board[nx][ny] == 1 &&
                dist[nx][ny] == -1) {
                dist[nx][ny] = dist[x][y] + 1;
                q.push({nx, ny});
            }
        }
    }

    return dist;
}

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    int N, M;
    std::cin >> N >> M;

    int sx, sy;
    std::vector<std::vector<int>> board(N, std::vector<int>(M));
    for (int i = 0; i < N; ++i)
        for (int j = 0; j < M; ++j) {
            std::cin >> board[i][j];
            if (board[i][j] == 2) {
                sx = i;
                sy = j;
            }
        }

    auto dist = bfs(sx, sy, board);
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < M; ++j)
            std::cout << (board[i][j] ? dist[i][j] : 0) << ' ';
        std::cout << '\n';
    }

    return 0;
}
