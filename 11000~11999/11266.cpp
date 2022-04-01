#include <algorithm>
#include <iostream>
#include <limits>
#include <vector>

void dfs(int root, int parent, const std::vector<std::vector<int>>& graph,
         std::vector<int>& visited, std::vector<bool>& result) {
    static std::vector<int> low(graph.size(), 0);
    static int timer = 0;

    visited[root] = low[root] = ++timer;
    int children = 0;

    for (int to : graph[root]) {
        if (to == parent) continue;

        if (visited[to]) {
            low[root] = std::min(low[root], visited[to]);
        } else {
            dfs(to, root, graph, visited, result);
            low[root] = std::min(low[root], low[to]);
            if (low[to] >= visited[root] && parent != -1) result[root] = true;
            ++children;
        }
    }

    if (parent == -1 && children > 1) result[root] = true;
}

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    int v, e;
    std::cin >> v >> e;

    std::vector<std::vector<int>> graph(v);
    for (int i = 0; i < e; ++i) {
        int a, b;
        std::cin >> a >> b;

        graph[a - 1].push_back(b - 1);
        graph[b - 1].push_back(a - 1);
    }

    std::vector<bool> cutPoints(v);
    std::vector<int> visited(v, 0);

    for (int i = 0; i < v; ++i)
        if (!visited[i]) dfs(i, -1, graph, visited, cutPoints);

    std::cout << std::count(cutPoints.begin(), cutPoints.end(), true) << '\n';
    for (int i = 0; i < v; ++i)
        if (cutPoints[i]) std::cout << i + 1 << '\n';

    return 0;
}
