#include <iostream>
#include <limits>
#include <queue>
#include <utility>
#include <vector>

int dijkstra(int s, int t,
             const std::vector<std::vector<std::pair<int, int>>>& adj) {
    const int& INF = std::numeric_limits<int>::max();
    std::vector<int> dist(adj.size(), INF);
    std::priority_queue<std::pair<int, int>> q;

    dist[s] = 0;
    q.push({0, s});

    while (!q.empty()) {
        auto [d, u] = q.top();
        q.pop();

        if (d == dist[u])
            for (const auto& [v, w] : adj[u])
                if (int newDist = d + w; newDist < dist[v]) {
                    dist[v] = newDist;
                    q.push({newDist, v});
                }
    }

    return dist[t];
}

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    int n, m;
    std::cin >> n >> m;

    std::vector<std::vector<std::pair<int, int>>> adj(n);
    for (int i = 0; i < m; ++i) {
        int u, v, w;
        std::cin >> u >> v >> w;

        adj[u - 1].push_back({v - 1, w});
    }

    int s, t;
    std::cin >> s >> t;

    std::cout << dijkstra(s - 1, t - 1, adj);

    return 0;
}