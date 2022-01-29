#include <algorithm>
#include <deque>
#include <iostream>
#include <queue>
#include <string>
#include <utility>
#include <vector>

int bfs(std::vector<std::vector<int>>& graph, int n, int m) {
    std::vector<std::vector<int>> visited(n, std::vector<int>(m));
    std::deque<std::pair<int, int>> q;

    q.push_back({0, 0});
    visited[0][0] = 1;

    while (!q.empty()) {
        auto [x, y] = q.front();
        q.pop_front();

        int dx[4] = {-1, 1, 0, 0};
        int dy[4] = {0, 0, -1, 1};

        for (int i = 0; i < 4; ++i) {
            int nx = x + dx[i];
            int ny = y + dy[i];

            if (0 <= nx && nx < n && 0 <= ny && ny < m && !visited[nx][ny]) {
                if (!graph[nx][ny]) {
                    q.push_front({nx, ny});
                    visited[nx][ny] = visited[x][y];
                } else if (graph[nx][ny] == -1) {
                    q.push_back({nx, ny});
                    visited[nx][ny] = visited[x][y] + 1;
                } else {
                    graph[nx][ny] = -1;
                }
            }
        }
    }

    int max = 0;
    for (const auto& i : visited)
        for (const auto& j : i)
            if (j > max) max = j;

    return max - 1;
}

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    int n, m;
    std::cin >> n >> m;

    std::vector<std::vector<int>> graph(n, std::vector<int>(m));
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < m; ++j) {
            int cell;
            std::cin >> cell;
            graph[i][j] = cell;
        }

    std::cout << bfs(graph, n, m);

    return 0;
}