#include <algorithm>
#include <iostream>
#include <limits>
#include <numeric>
#include <queue>
#include <vector>

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    int N, M;
    std::cin >> N >> M;

    std::vector<std::vector<int>> board(N, std::vector<int>(M));
    for (auto& row : board)
        for (auto& cell : row) std::cin >> cell;

    std::queue<std::tuple<bool, int, int>> q;
    std::vector<std::vector<std::vector<int>>> visited(
        2, std::vector<std::vector<int>>(
               N, std::vector<int>(M, std::numeric_limits<int>::max())));

    q.push({false, 0, 0});
    visited[0][0][0] = board[0][0];

    int dx[] = {0, 0, 1, -1};
    int dy[] = {1, -1, 0, 0};
    while (!q.empty()) {
        auto [used_device, x, y] = q.front();
        q.pop();

        for (int i = 0; i < 4; ++i) {
            int nx = x + dx[i];
            int ny = y + dy[i];
            if (nx < 0 || nx >= N || ny < 0 || ny >= M) continue;

            int cur_dist = std::max(visited[used_device][x][y], board[nx][ny]);
            if (cur_dist < visited[used_device][nx][ny]) {
                visited[used_device][nx][ny] = cur_dist;
                q.push({used_device, nx, ny});
            }

            if (!used_device) {
                nx = x + dx[i] * 2;
                ny = y + dy[i] * 2;
                if (nx < 0 || nx >= N || ny < 0 || ny >= M) continue;

                cur_dist = std::max(visited[used_device][x][y], board[nx][ny]);
                if (cur_dist < visited[1][nx][ny]) {
                    visited[1][nx][ny] = cur_dist;
                    q.push({true, nx, ny});
                }
            }
        }
    }

    std::cout << std::min(visited[0][N - 1][M - 1], visited[1][N - 1][M - 1])
              << '\n';

    return 0;
}
