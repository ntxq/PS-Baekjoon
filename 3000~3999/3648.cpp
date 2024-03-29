#include <algorithm>
#include <iostream>
#include <vector>

int N, M;
std::vector<std::vector<int>> adj, adj_rev;
std::vector<int> scc, order;
std::vector<bool> visited;

void dfs(int u) {
    visited[u] = true;
    for (int v : adj[u])
        if (!visited[v]) dfs(v);

    order.push_back(u);
}

void dfs_rev(int u, int cid) {
    visited[u] = true;
    scc[u] = cid;

    for (int v : adj_rev[u])
        if (!visited[v]) dfs_rev(v, cid);
}

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    while (std::cin >> N >> M) {
        adj.assign(2 * N + 1, std::vector<int>());
        adj_rev.assign(2 * N + 1, std::vector<int>());

        for (int i = 0; i < M; ++i) {
            int a, b;
            std::cin >> a >> b;

            adj[N - a].push_back(N + b);
            adj[N - b].push_back(N + a);

            adj_rev[N + a].push_back(N - b);
            adj_rev[N + b].push_back(N - a);
        }

        visited.assign(2 * N + 1, false);
        order.clear();

        dfs(N + 1);
        for (int i = 0; i <= 2 * N; ++i)
            if (!visited[i]) dfs(i);

        visited.assign(2 * N + 1, false);
        std::reverse(order.begin(), order.end());
        scc.assign(2 * N + 1, 0);

        int cid = 0;
        for (int u : order)
            if (!visited[u]) dfs_rev(u, cid++);

        bool isSat = scc[N + 1] >= scc[N - 1];
        for (int i = 1; i <= N && isSat; ++i)
            if (scc[N - i] == scc[N + i]) isSat = false;

        std::cout << (isSat ? "yes" : "no") << '\n';
    }

    return 0;
}