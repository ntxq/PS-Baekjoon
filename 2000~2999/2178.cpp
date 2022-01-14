#include <iostream>
#include <queue>
#include <utility>
#include <vector>

int bfs(const std::vector<std::vector<char>>& graph) {
    std::vector<std::vector<int>> dist(graph.size(),
                                       std::vector<int>(graph[0].size()));
    std::queue<std::pair<unsigned, unsigned>> q;

    q.push({0, 0});
    dist[0][0] = 1;

    while (!q.empty()) {
        auto [x, y] = q.front();
        q.pop();

        if (x > 0 && graph[x - 1][y] == '1' && !dist[x - 1][y]) {
            dist[x - 1][y] = dist[x][y] + 1;
            q.push({x - 1, y});
        }

        if (y > 0 && graph[x][y - 1] == '1' && !dist[x][y - 1]) {
            dist[x][y - 1] = dist[x][y] + 1;
            q.push({x, y - 1});
        }

        if (x < graph.size() - 1 && graph[x + 1][y] == '1' && !dist[x + 1][y]) {
            dist[x + 1][y] = dist[x][y] + 1;
            q.push({x + 1, y});
        }

        if (y < graph[0].size() - 1 && graph[x][y + 1] == '1' &&
            !dist[x][y + 1]) {
            dist[x][y + 1] = dist[x][y] + 1;
            q.push({x, y + 1});
        }
    }

    return dist.back().back();
}

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    int n, m;
    std::cin >> n >> m;

    std::vector<std::vector<char>> graph(n, std::vector<char>(m));
    for (auto& row : graph)
        for (auto& col : row) std::cin >> col;

    std::cout << bfs(graph);

    return 0;
}