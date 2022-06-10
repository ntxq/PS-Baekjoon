#include <algorithm>
#include <cmath>
#include <iostream>
#include <limits>
#include <utility>
#include <vector>

int LEN;
std::vector<std::vector<std::pair<int, int>>> adj;
std::vector<std::vector<int>> parent;
std::vector<long long> dist;
std::vector<int> depth;

void dfs(int u) {
    for (const auto& [v, w] : adj[u])
        if (depth[v] == -1) {
            parent[v][0] = u;
            dist[v] = dist[u] + w;
            depth[v] = depth[u] + 1;
            dfs(v);
        }
}

long long queryDist(int u, int v) {
    long long totalDist = dist[u] + dist[v];

    if (depth[u] < depth[v]) std::swap(u, v);

    for (int i = 0, diff = depth[u] - depth[v]; diff; ++i, diff /= 2)
        if (diff % 2) u = parent[u][i];

    if (u != v) {
        for (int i = LEN; i >= 0; --i)
            if (parent[u][i] && parent[u][i] != parent[v][i]) {
                u = parent[u][i];
                v = parent[v][i];
            }

        u = parent[u][0];
    }

    return totalDist - 2 * dist[u];
}

int queryParent(int u, int v, int k) {
    int tempU = u;
    int tempV = v;

    if (depth[u] < depth[v]) std::swap(u, v);

    for (int i = 0, diff = depth[u] - depth[v]; diff; ++i, diff /= 2)
        if (diff % 2) u = parent[u][i];

    if (u != v) {
        for (int i = LEN; i >= 0; --i)
            if (parent[u][i] && parent[u][i] != parent[v][i]) {
                u = parent[u][i];
                v = parent[v][i];
            }

        u = parent[u][0];
    }

    int cnt = depth[tempU] - depth[u] + 1;

    if (k == cnt)
        return u;
    else if (k < cnt) {
        --k;

        for (int i = 0; k; ++i, k /= 2)
            if (k % 2) tempU = parent[tempU][i];

        return tempU;
    } else {
        k -= cnt;
        k = depth[tempV] - depth[u] - k;

        for (int i = 0; k; ++i, k /= 2)
            if (k % 2) tempV = parent[tempV][i];

        return tempV;
    }
}

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    int N;
    std::cin >> N;

    LEN = std::ceil(std::log2(N)) + 1;
    adj.resize(N + 1);
    parent.assign(N + 1, std::vector<int>(LEN + 1));
    dist.resize(N + 1);
    depth.assign(N + 1, -1);

    for (int i = 1; i < N; ++i) {
        int u, v, w;
        std::cin >> u >> v >> w;

        adj[u].push_back({v, w});
        adj[v].push_back({u, w});
    }

    parent[1][0] = 0;
    dist[1] = 0;
    depth[1] = 0;

    dfs(1);

    for (int j = 1; j <= LEN; ++j)
        for (int i = 1; i <= N; ++i)
            parent[i][j] = parent[parent[i][j - 1]][j - 1];

    int M;
    std::cin >> M;

    while (M--) {
        int q;
        std::cin >> q;

        int u, v, k;
        switch (q) {
            case 1:
                std::cin >> u >> v;
                std::cout << queryDist(u, v) << '\n';
                break;
            case 2:
                std::cin >> u >> v >> k;
                std::cout << queryParent(u, v, k) << '\n';
                break;
        }
    }

    return 0;
}