#include <algorithm>
#include <iostream>
#include <vector>

bool dfs(int s, std::vector<int>& topology, std::vector<int>& visited,
         const std::vector<std::vector<int>>& adj) {
    visited[s] = 1;

    bool has_cycle = false;
    for (decltype(adj[s].size()) i = 0; i < adj[s].size() && !has_cycle; ++i) {
        int t = adj[s][i];

        if (visited[t] == 1)
            has_cycle = true;
        else if (!visited[t])
            has_cycle = dfs(t, topology, visited, adj);
    }

    visited[s] = 2;
    topology.push_back(s);

    return has_cycle;
}

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    int n, m;
    std::cin >> n >> m;

    std::vector<std::vector<int>> adj(n);
    for (int i = 0; i < m; ++i) {
        int k;
        std::cin >> k;

        int u, v;
        std::cin >> v;
        for (int j = 1; j < k; ++j) {
            std::cin >> u;
            adj[u - 1].push_back(v - 1);
            v = u;
        }
    }

    std::vector<int> topology;
    std::vector<int> visisted(n);

    bool has_cycle = false;
    for (int i = 0; i < n && !has_cycle; ++i)
        if (!visisted[i]) has_cycle = dfs(i, topology, visisted, adj);

    if (has_cycle)
        std::cout << 0 << '\n';
    else
        for (const int& i : topology) std::cout << i + 1 << '\n';

    return 0;
}