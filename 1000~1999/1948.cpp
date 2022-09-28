#include <iostream>
#include <queue>
#include <utility>
#include <vector>

int bfs(const std::vector<std::vector<std::pair<int, int>>>& adj,
        std::vector<int>& dist, int s, int t) {
    std::queue<int> q;

    dist[s] = 0;
    q.push(s);

    while (!q.empty()) {
        int u = q.front();
        q.pop();

        for (auto [v, w] : adj[u])
            if (dist[v] < dist[u] + w) {
                dist[v] = dist[u] + w;
                q.push(v);
            }
    }

    return dist[t];
}

int count(const std::vector<std::vector<std::pair<int, int>>>& adj,
          const std::vector<int>& dist, int t, int maxDist) {
    std::vector<bool> visited(adj.size());
    std::queue<std::pair<int, int>> q;

    visited[t] = true;
    q.push({t, maxDist});

    int count = 0;
    while (!q.empty()) {
        auto [v, d] = q.front();
        q.pop();

        for (auto [u, w] : adj[v])
            if (dist[u] == d - w) {
                ++count;
                if (!visited[u]) {
                    visited[u] = true;
                    q.push({u, d - w});
                }
            }
    }

    return count;
}

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    int n, m;
    std::cin >> n >> m;

    std::vector<std::vector<std::pair<int, int>>> adj(n + 1);
    std::vector<std::vector<std::pair<int, int>>> adjRev(n + 1);

    for (int i = 0; i < m; ++i) {
        int u, v, w;
        std::cin >> u >> v >> w;

        adj[u].push_back({v, w});
        adjRev[v].push_back({u, w});
    }

    int s, t;
    std::cin >> s >> t;

    std::vector<int> dist(n + 1, -1);
    int maxDist = bfs(adj, dist, s, t);

    std::cout << maxDist << '\n' << count(adjRev, dist, t, maxDist) << '\n';

    return 0;
}