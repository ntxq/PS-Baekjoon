#include <algorithm>
#include <iostream>
#include <limits>
#include <numeric>
#include <queue>
#include <vector>

std::vector<long long> dijkstrak(
    int s, const std::vector<std::vector<std::pair<int, int>>>& adj) {
    std::vector<long long> dist(adj.size(),
                                std::numeric_limits<long long>::max());
    std::priority_queue<std::pair<long long, int>,
                        std::vector<std::pair<long long, int>>,
                        std::greater<std::pair<long long, int>>>
        pq;

    dist[s] = 0;
    pq.push({0, s});

    while (!pq.empty()) {
        auto [d, u] = pq.top();
        pq.pop();

        for (auto [v, w] : adj[u])
            if (dist[v] > dist[u] + w) {
                dist[v] = dist[u] + w;
                pq.push({dist[v], v});
            }
    }

    return dist;
}

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    int N, M;
    std::cin >> N >> M;

    std::vector<std::vector<std::pair<int, int>>> adj(N);
    for (int i = 0; i < M; ++i) {
        int u, v, w;
        std::cin >> u >> v >> w;

        adj[u - 1].push_back({v - 1, w});
        adj[v - 1].push_back({u - 1, w});
    }

    int s, t;
    std::cin >> s >> t;
    --s, --t;

    int P;
    std::cin >> P;

    std::vector<int> p;
    for (int i = 0; i < P; ++i) {
        int y;
        std::cin >> y;
        p.push_back(y - 1);
    }

    std::vector<std::vector<long long>> dist;
    for (int i = 0; i < P; ++i) dist.emplace_back(dijkstrak(p[i], adj));

    long long min_dist = std::numeric_limits<long long>::max();
    for (int i = 0; i < P; ++i) {
        if (dist[i][s] == std::numeric_limits<long long>::max()) continue;
        for (int j = 0; j < P; ++j) {
            if (i == j ||
                dist[j][p[i]] == std::numeric_limits<long long>::max())
                continue;
            for (int k = 0; k < P; ++k) {
                if (i == k || j == k ||
                    dist[k][p[j]] == std::numeric_limits<long long>::max() ||
                    dist[k][t] == std::numeric_limits<long long>::max())
                    continue;

                long long cur_dist =
                    dist[i][s] + dist[j][p[i]] + dist[k][p[j]] + dist[k][t];

                min_dist = std::min(min_dist, cur_dist);
            }
        }
    }

    std::cout << (min_dist == std::numeric_limits<long long>::max() ? -1
                                                                    : min_dist)
              << '\n';

    return 0;
}
