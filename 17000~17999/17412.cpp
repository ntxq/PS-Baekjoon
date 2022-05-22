#include <algorithm>
#include <iostream>
#include <queue>
#include <vector>

bool bfs(int s, int t, const std::vector<std::vector<int>>& adj,
         const std::vector<std::vector<bool>>& capacity,
         std::vector<int>& parent) {
    std::queue<int> q;

    std::fill(parent.begin(), parent.end(), -1);
    q.push(s);
    parent[s] = s;

    while (!q.empty() && parent[t] == -1) {
        int u = q.front();
        q.pop();

        for (int v : adj[u])
            if (capacity[u][v] && parent[v] == -1) {
                q.push(v);
                parent[v] = u;
            }
    }

    return parent[t] != -1;
}

int maxflow(int s, int t, const std::vector<std::vector<int>>& adj,
            std::vector<std::vector<bool>>& capacity) {
    int flow = 0;

    std::vector<int> parent(adj.size());
    while (bfs(s, t, adj, capacity, parent)) {
        ++flow;

        int cur = t;
        while (cur != parent[cur]) {
            int prev = parent[cur];
            capacity[prev][cur] = false;
            capacity[cur][prev] = true;
            cur = prev;
        }
    }

    return flow;
}

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    int N, P;
    std::cin >> N >> P;

    std::vector<std::vector<int>> adj(N + 1);
    std::vector<std::vector<bool>> capacity(N + 1, std::vector<bool>(N + 1));

    for (int i = 0; i < P; ++i) {
        int u, v;
        std::cin >> u >> v;

        adj[u].push_back(v);
        adj[v].push_back(u);

        capacity[u][v] = true;
    }

    std::cout << maxflow(1, 2, adj, capacity) << '\n';

    return 0;
}