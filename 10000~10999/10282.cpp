#include <algorithm>
#include <iostream>
#include <limits>
#include <numeric>
#include <queue>
#include <vector>

void dijkstra(int s, int N,
              const std::vector<std::vector<std::pair<int, int>>>& adj) {
    std::vector<int> dist(N, std::numeric_limits<int>::max());
    std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>,
                        std::greater<std::pair<int, int>>>
        pq;

    dist[s] = 0;
    pq.push({0, s});

    while (!pq.empty()) {
        auto [d, u] = pq.top();
        pq.pop();

        if (d > dist[u]) continue;

        for (auto [v, w] : adj[u])
            if (dist[v] > dist[u] + w) {
                dist[v] = dist[u] + w;
                pq.push({dist[v], v});
            }
    }

    int cnt = 0;
    int maxDist = 0;
    for (int i = 0; i < N; ++i)
        if (dist[i] != std::numeric_limits<int>::max()) {
            ++cnt;
            maxDist = std::max(maxDist, dist[i]);
        }

    std::cout << cnt << ' ' << maxDist << '\n';
}

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    int T;
    std::cin >> T;

    while (T--) {
        int N, M, s;
        std::cin >> N >> M >> s;

        std::vector<std::vector<std::pair<int, int>>> adj(N);
        for (int i = 0; i < M; ++i) {
            int u, v, w;
            std::cin >> v >> u >> w;

            adj[u - 1].push_back({v - 1, w});
        }

        dijkstra(s - 1, N, adj);
    }

    return 0;
}
