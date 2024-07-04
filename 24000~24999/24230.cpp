#include <algorithm>
#include <iostream>
#include <limits>
#include <numeric>
#include <vector>

int dfs(int u, int prev, int prevColor, const std::vector<int>& colors,
        const std::vector<std::vector<int>>& adj) {
    int result = colors[u] != prevColor;

    for (int v : adj[u])
        if (v != prev) result += dfs(v, u, colors[u], colors, adj);

    return result;
}

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    int N;
    std::cin >> N;

    std::vector<int> colors(N);
    for (auto& color : colors) std::cin >> color;

    std::vector<std::vector<int>> adj(N);
    for (int i = 0; i < N - 1; ++i) {
        int u, v;
        std::cin >> u >> v;

        adj[u - 1].push_back(v - 1);
        adj[v - 1].push_back(u - 1);
    }

    std::cout << dfs(0, 0, 0, colors, adj) << '\n';

    return 0;
}
