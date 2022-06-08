#include <algorithm>
#include <cmath>
#include <iostream>
#include <limits>
#include <utility>
#include <vector>

std::vector<std::vector<int>> parent, minRoad, maxRoad;
std::vector<int> height;
std::vector<bool> visited;

void dfs(int u, int h,
         const std::vector<std::vector<std::pair<int, int>>>& adj) {
    visited[u] = true;
    height[u] = h;

    for (const auto& [v, w] : adj[u])
        if (!visited[v]) {
            parent[v][0] = u;
            minRoad[v][0] = maxRoad[v][0] = w;
            dfs(v, h + 1, adj);
        }
}

std::pair<int, int> lca(int u, int v) {
    if (height[u] > height[v]) std::swap(u, v);

    int l = std::numeric_limits<int>::max();
    int r = std::numeric_limits<int>::min();

    int diff = height[v] - height[u];
    for (int i = 0; diff; ++i) {
        if (diff % 2) {
            l = std::min(l, minRoad[v][i]);
            r = std::max(r, maxRoad[v][i]);
            v = parent[v][i];
        }

        diff /= 2;
    }

    if (u == v) return {l, r};

    for (unsigned i = parent[u].size() - 1; i < parent[u].size(); --i)
        if (parent[u][i] != parent[v][i]) {
            l = std::min({l, minRoad[u][i], minRoad[v][i]});
            r = std::max({r, maxRoad[u][i], maxRoad[v][i]});
            u = parent[u][i];
            v = parent[v][i];
        }

    l = std::min({l, minRoad[u][0], minRoad[v][0]});
    r = std::max({r, maxRoad[u][0], maxRoad[v][0]});

    return {l, r};
}

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    int N;
    std::cin >> N;

    std::vector<std::vector<std::pair<int, int>>> adj(N + 1);
    for (int i = 1; i < N; ++i) {
        int u, v, w;
        std::cin >> u >> v >> w;

        adj[u].push_back({v, w});
        adj[v].push_back({u, w});
    }

    const int LEN = std::ceil(std::log2(N)) + 1;

    visited.resize(N + 1);
    height.resize(N + 1);
    parent.resize(N + 1, std::vector<int>(LEN));
    minRoad.resize(N + 1, std::vector<int>(LEN));
    maxRoad.resize(N + 1, std::vector<int>(LEN));

    dfs(1, 0, adj);

    for (int j = 1; j < LEN; ++j)
        for (int i = 1; i <= N; ++i) {
            parent[i][j] = parent[parent[i][j - 1]][j - 1];
            minRoad[i][j] =
                std::min(minRoad[i][j - 1], minRoad[parent[i][j - 1]][j - 1]);
            maxRoad[i][j] =
                std::max(maxRoad[i][j - 1], maxRoad[parent[i][j - 1]][j - 1]);
        }

    int K;
    std::cin >> K;

    for (int i = 0; i < K; ++i) {
        int u, v;
        std::cin >> u >> v;

        auto [minW, maxW] = lca(u, v);
        std::cout << minW << " " << maxW << "\n";
    }

    return 0;
}