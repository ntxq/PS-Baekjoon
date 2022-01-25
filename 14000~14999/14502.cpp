#include <iostream>
#include <queue>
#include <utility>
#include <vector>

int bfs(const std::vector<std::vector<int>>& map,
        const std::queue<std::pair<int, int>>& virus, int n, int m) {
    auto graph(map);
    auto q(virus);

    while (!q.empty()) {
        auto [x, y] = q.front();
        q.pop();

        std::vector<int> dx{1, -1, 0, 0};
        std::vector<int> dy{0, 0, 1, -1};

        for (int i = 0; i < 4; ++i) {
            auto nx = x + dx[i];
            auto ny = y + dy[i];

            if (0 <= nx && nx < n && 0 <= ny && ny < m && !graph[nx][ny]) {
                graph[nx][ny] = 2;
                q.push({nx, ny});
            }
        }
    }

    int count = 0;
    for (auto& i : graph)
        for (auto& j : i)
            if (!j) ++count;

    return count;
}

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    int n, m;
    std::cin >> n >> m;

    std::vector<std::vector<int>> graph(n, std::vector<int>(m));
    std::queue<std::pair<int, int>> q;

    for (int i = 0; i < n; ++i)
        for (int j = 0; j < m; ++j) {
            std::cin >> graph[i][j];

            if (graph[i][j] == 2) q.push({i, j});
        }

    int maxSafe = 0;
    for (int i = 0; i < n * m; ++i)
        for (int j = i + 1; j < n * m; ++j)
            for (int k = j + 1; k < n * m; ++k)
                if (!graph[i / m][i % m] && !graph[j / m][j % m] &&
                    !graph[k / m][k % m]) {
                    graph[i / m][i % m] = 1;
                    graph[j / m][j % m] = 1;
                    graph[k / m][k % m] = 1;

                    if (int curSafe = bfs(graph, q, n, m); curSafe > maxSafe)
                        maxSafe = curSafe;

                    graph[i / m][i % m] = 0;
                    graph[j / m][j % m] = 0;
                    graph[k / m][k % m] = 0;
                }

    std::cout << maxSafe;

    return 0;
}