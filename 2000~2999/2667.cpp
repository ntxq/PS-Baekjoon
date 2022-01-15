#include <algorithm>
#include <iostream>
#include <queue>
#include <utility>
#include <vector>

int bfs(const std::vector<std::vector<char>>& graph,
        std::vector<std::vector<bool>>& visited, int x, int y) {
    std::queue<std::pair<unsigned, unsigned>> q;

    q.push({x, y});
    visited[x][y] = true;

    int count = 0;
    while (!q.empty()) {
        ++count;

        auto [x, y] = q.front();
        q.pop();

        if (x > 0 && graph[x - 1][y] == '1' && !visited[x - 1][y]) {
            q.push({x - 1, y});
            visited[x - 1][y] = true;
        }

        if (x < graph.size() - 1 && graph[x + 1][y] == '1' &&
            !visited[x + 1][y]) {
            q.push({x + 1, y});
            visited[x + 1][y] = true;
        }

        if (y > 0 && graph[x][y - 1] == '1' && !visited[x][y - 1]) {
            q.push({x, y - 1});
            visited[x][y - 1] = true;
        }

        if (y < graph[0].size() - 1 && graph[x][y + 1] == '1' &&
            !visited[x][y + 1]) {
            q.push({x, y + 1});
            visited[x][y + 1] = true;
        }
    }

    return count;
}

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    int n;
    std::cin >> n;

    std::vector<std::vector<char>> graph(n, std::vector<char>(n));
    for (auto& row : graph)
        for (auto& col : row) std::cin >> col;

    std::vector<std::vector<bool>> visited(n, std::vector<bool>(n));
    std::vector<int> count;

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (graph[i][j] == '1' && !visited[i][j]) {
                count.push_back(bfs(graph, visited, i, j));
            }
        }
    }

    std::sort(count.begin(), count.end());

    std::cout << count.size() << '\n';
    for (const int& i : count) std::cout << i << '\n';

    return 0;
}