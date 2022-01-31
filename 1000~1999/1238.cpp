#include <iostream>
#include <limits>
#include <queue>
#include <utility>
#include <vector>

std::vector<int> dijkstra(
    const std::vector<std::vector<std::pair<int, int>>>& adj, int s) {
    std::vector<int> dist(adj.size(), std::numeric_limits<int>::max());
    std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>,
                        std::greater<std::pair<int, int>>>
        pq;

    dist[s] = 0;
    pq.push({0, s});

    while (!pq.empty()) {
        auto [d, u] = pq.top();
        pq.pop();

        if (d == dist[u]) {
            for (const auto& [v, w] : adj[u])
                if (int newD = d + w; newD < dist[v]) {
                    dist[v] = newD;
                    pq.push({newD, v});
                }
        }
    }

    return dist;
}

int dijkstra(const std::vector<std::vector<std::pair<int, int>>>& adj, int s,
             int t) {
    return dijkstra(adj, s)[t];
}

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    int n, m, x;
    std::cin >> n >> m >> x;

    std::vector<std::vector<std::pair<int, int>>> adj(n);
    for (int i = 0; i < m; ++i) {
        int u, v, w;
        std::cin >> u >> v >> w;

        adj[u - 1].push_back({v - 1, w});
    }

    auto returnDist = dijkstra(adj, x - 1);

    int maxDist = 0;
    for (int i = 0; i < n; ++i) {
        int dist = dijkstra(adj, i, x - 1) + returnDist[i];
        if (dist > maxDist) maxDist = dist;
    }

    std::cout << maxDist;

    return 0;
}