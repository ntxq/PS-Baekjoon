#include <iostream>
#include <queue>
#include <vector>

bool dfs(int u, int p, int& s, int& t, std::vector<bool>& visited,
         std::vector<int>& parent, const std::vector<std::vector<int>>& adj) {
    visited[u] = true;
    for (const auto& v : adj[u]) {
        if (v == p) continue;

        if (visited[v]) {
            s = v;
            t = u;
            return true;
        }

        parent[v] = u;
        if (dfs(v, u, s, t, visited, parent, adj)) return true;
    }

    return false;
}

void bfs(std::vector<int>& dist, int s, int t,
         const std::vector<std::vector<int>>& adj,
         const std::vector<int>& parent) {
    std::queue<int> q;

    while (s != t) {
        dist[t] = 0;
        q.push(t);
        t = parent[t];
    }

    dist[s] = 0;
    q.push(s);

    while (!q.empty()) {
        int u = q.front();
        q.pop();

        for (const auto& v : adj[u])
            if (dist[v] == -1) {
                dist[v] = dist[u] + 1;
                q.push(v);
            }
    }
}

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    int N;
    std::cin >> N;

    std::vector<std::vector<int>> adj(N);

    for (int i = 0; i < N; ++i) {
        int u, v;
        std::cin >> u >> v;
        --u, --v;

        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    std::vector<bool> visited(N);
    std::vector<int> parent(N, -1);
    int cycleStart = -1, cycleEnd = -1;
    dfs(0, -1, cycleStart, cycleEnd, visited, parent, adj);

    std::vector<int> dist(N, -1);
    bfs(dist, cycleStart, cycleEnd, adj, parent);

    for (const auto& d : dist) std::cout << d << ' ';
    std::cout << '\n';

    return 0;
}
