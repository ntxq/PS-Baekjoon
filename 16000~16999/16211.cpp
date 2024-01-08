#include <algorithm>
#include <iostream>
#include <limits>
#include <numeric>
#include <queue>
#include <vector>

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    int N, M, K;
    std::cin >> N >> M >> K;

    std::vector<std::vector<std::pair<int, int>>> adj(N);
    for (int i = 0; i < M; ++i) {
        int u, v, w;
        std::cin >> u >> v >> w;
        adj[u - 1].push_back({v - 1, w});
        adj[v - 1].push_back({u - 1, w});
    }

    std::priority_queue<std::pair<long long, int>,
                        std::vector<std::pair<long long, int>>,
                        std::greater<std::pair<long long, int>>>
        pq;
    std::vector<long long> dist(N, std::numeric_limits<long long>::max());

    for (int i = 0; i < K; ++i) {
        int s;
        std::cin >> s;
        pq.push({0, s - 1});
        dist[s - 1] = 0;
    }

    while (!pq.empty()) {
        auto [d, u] = pq.top();
        pq.pop();

        if (dist[u] < d) continue;

        for (auto [v, w] : adj[u]) {
            if (dist[v] > dist[u] + w) {
                dist[v] = dist[u] + w;
                pq.push({dist[v], v});
            }
        }
    }

    std::vector<int> safeplaces;
    pq.push({0, 0});
    dist[0] = 0;

    while (!pq.empty()) {
        auto [d, u] = pq.top();
        pq.pop();

        if (dist[u] < d) continue;

        safeplaces.push_back(u);
        for (auto [v, w] : adj[u]) {
            if (dist[v] > dist[u] + w) {
                dist[v] = dist[u] + w;
                pq.push({dist[v], v});
            }
        }
    }

    std::sort(safeplaces.begin(), safeplaces.end());
    safeplaces.erase(std::unique(safeplaces.begin(), safeplaces.end()),
                     safeplaces.end());
    if (safeplaces.size() == 1) {
        std::cout << "0\n";
    } else {
        for (int i = 1; i < safeplaces.size(); ++i)
            std::cout << safeplaces[i] + 1 << ' ';
        std::cout << '\n';
    }

    return 0;
}
