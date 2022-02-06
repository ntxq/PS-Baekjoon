#include <cmath>
#include <functional>
#include <iostream>
#include <queue>
#include <utility>
#include <vector>

int dijkstra(const std::vector<std::vector<std::pair<int, int>>>& adj, int s) {
    std::vector<int> dist(adj.size(), std::numeric_limits<int>::max());
    std::queue<std::pair<int, int>> q;

    dist[s] = 0;
    q.push({0, s});

    while (!q.empty()) {
        auto [d, u] = q.front();
        q.pop();

        if (d == dist[u])
            for (auto [v, w] : adj[u])
                if (dist[v] > dist[u] + w) {
                    dist[v] = dist[u] + w;
                    q.push({dist[v], v});
                }
    }

    return std::abs(*std::min_element(dist.cbegin(), dist.cend()));
}

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    int t;
    std::cin >> t;

    for (int i = 0; i < t; ++i) {
        int n, k;
        std::cin >> n >> k;

        std::vector<int> weight(n);
        for (int& j : weight) std::cin >> j;

        std::vector<std::vector<std::pair<int, int>>> adj(n);
        for (int j = 0; j < k; ++j) {
            int u, v;
            std::cin >> u >> v;

            adj[v - 1].push_back({u - 1, -weight[u - 1]});
        }

        int w;
        std::cin >> w;

        std::cout << dijkstra(adj, w - 1) + weight[w - 1] << '\n';
    }

    return 0;
}