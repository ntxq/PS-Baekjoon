#include <algorithm>
#include <iostream>
#include <limits>
#include <numeric>
#include <queue>
#include <vector>

int dijkstra(const std::vector<std::vector<std::tuple<int, int, int>>>& adj,
             int N, int M) {
    std::priority_queue<std::tuple<int, int, int>,
                        std::vector<std::tuple<int, int, int>>,
                        std::greater<std::tuple<int, int, int>>>
        pq;
    std::vector<std::vector<int>> dist(
        N, std::vector<int>(M + 1, std::numeric_limits<int>::max()));

    pq.push({0, 0, 0});
    for (int i = 0; i <= M; ++i) dist[0][i] = 0;

    while (!pq.empty()) {
        auto [prevDist, prevCost, prevNode] = pq.top();
        pq.pop();

        for (auto [nextNode, nextCost, nextDist] : adj[prevNode]) {
            int nCost = prevCost + nextCost;
            int nDist = prevDist + nextDist;

            if (nCost <= M && nDist < dist[nextNode][nCost]) {
                dist[nextNode][nCost] = nDist;
                pq.push({nDist, nCost, nextNode});
            }
        }
    }

    return *std::min_element(dist[N - 1].begin(), dist[N - 1].end());
}

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    int T;
    std::cin >> T;

    while (T--) {
        int N, M, K;
        std::cin >> N >> M >> K;

        std::vector<std::vector<std::tuple<int, int, int>>> adj(N);
        for (int i = 0; i < K; ++i) {
            int u, v, c, d;
            std::cin >> u >> v >> c >> d;

            adj[u - 1].push_back({v - 1, c, d});
        }

        int ans = dijkstra(adj, N, M);
        if (ans == std::numeric_limits<int>::max()) {
            std::cout << "Poor KCM\n";
        } else {
            std::cout << ans << '\n';
        }
    }

    return 0;
}