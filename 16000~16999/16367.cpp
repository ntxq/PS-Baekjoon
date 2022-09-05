#include <algorithm>
#include <iostream>
#include <vector>

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

    int k, n;
    std::cin >> k >> n;

    adj.resize(2 * k + 1);
    adj_rev.resize(2 * k + 1);

    for (int i = 0; i < n; ++i) {
        int l[3];
        char c[3];

        for (int j = 0; j < 3; ++j) {
            std::cin >> l[j] >> c[j];
            if (c[j] == 'R') l[j] *= -1;
        }

        for (int j = 0; j < 3; ++j) {
            adj[k - l[j]].push_back(k + l[(j + 1) % 3]);
            adj[k - l[(j + 1) % 3]].push_back(k + l[j]);
            adj_rev[k + l[j]].push_back(k - l[(j + 1) % 3]);
            adj_rev[k + l[(j + 1) % 3]].push_back(k - l[j]);
        }
    }

    visited.resize(2 * k + 1);
    for (int i = 0; i < 2 * k + 1; ++i)
        if (!visited[i]) dfs(i);

    visited.assign(2 * k + 1, false);
    std::reverse(order.begin(), order.end());
    scc.resize(2 * k + 1);

    int cid = 0;
    for (int u : order)
        if (!visited[u]) dfs_rev(u, cid++);

    bool isSat = true;
    for (int i = 1; i < k + 1 && isSat; ++i)
        if (scc[k - i] == scc[k + i]) isSat = false;

    if (isSat)
        for (int i = 1; i < k + 1; ++i)
            std::cout << (scc[k + i] < scc[k - i] ? 'R' : 'B');
    else
        std::cout << -1;
    std::cout << '\n';

    return 0;
}