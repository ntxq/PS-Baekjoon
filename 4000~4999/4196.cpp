#include <algorithm>
#include <iostream>
#include <ranges>
#include <vector>

std::vector<std::vector<int>> adj, adj_rev;
std::vector<int> order, component, inDegree;
std::vector<bool> visited;

void dfs(int u) {
    visited[u] = true;

    for (int v : adj[u])
        if (!visited[v]) dfs(v);

    order.push_back(u);
}

void dfs_rev(int u, int id) {
    visited[u] = true;
    component[u] = id;

    for (int v : adj_rev[u])
        if (!visited[v]) dfs_rev(v, id);
}

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    int T;
    std::cin >> T;

    while (T--) {
        int N, M;
        std::cin >> N >> M;

        adj.assign(N + 1, std::vector<int>());
        adj_rev.assign(N + 1, std::vector<int>());
        for (int i = 0; i < M; ++i) {
            int u, v;
            std::cin >> u >> v;

            adj[u].push_back(v);
            adj_rev[v].push_back(u);
        }

        visited.assign(N + 1, false);
        order.clear();

        for (int i = 1; i <= N; ++i)
            if (!visited[i]) dfs(i);

        visited.assign(N + 1, false);
        std::reverse(order.begin(), order.end());
        component.assign(N + 1, 0);
        inDegree.clear();

        int id = 0;
        for (int u : order)
            if (!visited[u]) {
                dfs_rev(u, id++);
                inDegree.push_back(0);
            }

        for (int u = 1; u <= N; ++u)
            for (int v : adj[u])
                if (component[u] != component[v]) ++inDegree[component[v]];

        int count = 0;
        for (int degree : inDegree)
            if (!degree) ++count;

        std::cout << count << '\n';
    }

    return 0;
}