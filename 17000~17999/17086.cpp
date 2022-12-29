#include <iostream>
#include <limits>
#include <queue>
#include <vector>

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    int N, M;
    std::cin >> N >> M;

    std::queue<std::pair<int, int>> q;
    std::vector<std::vector<int>> dist(
        N, std::vector<int>(M, std::numeric_limits<int>::max()));

    for (int i = 0; i < N; ++i)
        for (int j = 0; j < M; ++j)
            if (int s; std::cin >> s && s) {
                dist[i][j] = 0;
                q.push({i, j});
            }

    int dx[] = {1, 1, 1, 0, -1, -1, -1, 0};
    int dy[] = {1, 0, -1, -1, -1, 0, 1, 1};

    while (!q.empty()) {
        auto [x, y] = q.front();
        q.pop();

        for (int i = 0; i < 8; ++i)
            if (int nx = x + dx[i], ny = y + dy[i];
                0 <= nx && nx < N && 0 <= ny && ny < M &&
                dist[x][y] + 1 < dist[nx][ny]) {
                dist[nx][ny] = dist[x][y] + 1;
                q.push({nx, ny});
            }
    }

    int maxDist = 0;
    for (int i = 0; i < N; ++i)
        for (int j = 0; j < M; ++j)
            if (dist[i][j] > maxDist) maxDist = dist[i][j];

    std::cout << maxDist << '\n';

    return 0;
}
