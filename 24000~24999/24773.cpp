#include <algorithm>
#include <array>
#include <iomanip>
#include <iostream>
#include <limits>
#include <numeric>
#include <string>
#include <vector>

bool dfs(int u, int p, std::vector<bool>& visited, std::vector<int>& tin,
         std::vector<int>& low, int& timer,
         const std::vector<std::vector<int>>& graph) {
    visited[u] = true;
    tin[u] = low[u] = timer++;

    for (int v : graph[u]) {
        if (v == p) continue;

        if (visited[v])
            low[u] = std::min(low[u], tin[v]);
        else {
            if (dfs(v, u, visited, tin, low, timer, graph)) return true;
            low[u] = std::min(low[u], low[v]);
            if (low[v] > tin[u]) return true;
        }
    }

    return false;
}

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    int N, M;
    while (std::cin >> N >> M && (N || M)) {
        std::vector<std::vector<int>> graph(N);
        for (int i = 0; i < M; ++i) {
            int u, v;
            std::cin >> u >> v;
            graph[u].push_back(v);
            graph[v].push_back(u);
        }

        std::vector<bool> visited(N);
        std::vector<int> tin(N, -1), low(N, -1);
        int timer = 0;

        bool has_bridge = dfs(0, -1, visited, tin, low, timer, graph);
        for (int i = 0; i < N; ++i)
            if (!visited[i]) has_bridge = true;

        std::cout << (has_bridge ? "Yes" : "No") << '\n';
    }

    return 0;
}
