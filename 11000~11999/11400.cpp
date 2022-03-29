#include <algorithm>
#include <iostream>
#include <limits>
#include <vector>

void dfs(int root, int parent, const std::vector<std::vector<int>>& graph,
         std::vector<std::pair<int, int>>& result) {
    static std::vector<int> visited(graph.size(), 0);
    static std::vector<int> low(graph.size(), 0);
    static int timer = 0;

    visited[root] = low[root] = ++timer;
    for (int to : graph[root]) {
        if (to == parent) continue;

        if (visited[to]) {
            low[root] = std::min(low[root], visited[to]);
        } else {
            dfs(to, root, graph, result);
            low[root] = std::min(low[root], low[to]);
            if (low[to] > visited[root]) {
                if (root < to)
                    result.push_back({root, to});
                else
                    result.push_back({to, root});
            }
        }
    }
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

    std::vector<std::pair<int, int>> bridges;
    dfs(0, -1, graph, bridges);
    std::sort(bridges.begin(), bridges.end());

    std::cout << bridges.size() << '\n';
    for (auto [a, b] : bridges) {
        std::cout << a + 1 << ' ' << b + 1 << '\n';
    }

    return 0;
}
