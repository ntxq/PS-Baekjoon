#include <algorithm>
#include <cmath>
#include <iostream>
#include <limits>
#include <numeric>
#include <queue>
#include <vector>

int dijkstra(int N, int X,
             const std::vector<std::vector<std::tuple<int, int, int>>>& graph) {
    std::priority_queue<std::tuple<int, int, int, int>,
                        std::vector<std::tuple<int, int, int, int>>,
                        std::greater<>>
        pq;
    std::vector<double> dist(N, std::numeric_limits<double>::max());

    pq.push({0, 0, std::numeric_limits<int>::max(), 0});
    dist[0] = 0;

    double targetTime = std::numeric_limits<double>::max();

    while (!pq.empty()) {
        auto [_, lu, cu, u] = pq.top();
        pq.pop();

        for (const auto& [l, c, v] : graph[u]) {
            double nDist = lu + l + static_cast<double>(X) / std::min(cu, c);
            if (nDist < dist[v]) {
                dist[v] = nDist;
                pq.push({nDist, lu + l, std::min(cu, c), v});
            }

            if (v == N - 1) {
                double curTime =
                    lu + l + static_cast<double>(X) / std::min(cu, c);
                targetTime = std::min(targetTime, curTime);
            }
        }
    }

    return std::floor(targetTime);
}

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    int N, M, X;
    std::cin >> N >> M >> X;

    std::vector<std::vector<std::tuple<int, int, int>>> graph(N);
    for (int i = 0; i < M; ++i) {
        int u, v, l, c;
        std::cin >> u >> v >> l >> c;
        graph[u - 1].push_back({l, c, v - 1});
        graph[v - 1].push_back({l, c, u - 1});
    }

    std::cout << dijkstra(N, X, graph) << '\n';

    return 0;
}
