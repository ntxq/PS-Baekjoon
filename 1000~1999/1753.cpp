#include <functional>
#include <iostream>
#include <limits>
#include <queue>
#include <utility>
#include <vector>

std::vector<int> dijkstra(
    int root, const std::vector<std::vector<std::pair<int, int>>>& graph) {
    std::vector<int> dist(graph.size(), std::numeric_limits<int>::max());
    dist[root] = 0;

    std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>,
                        std::greater<std::pair<int, int>>>
        pq;
    pq.push({0, root});

    while (!pq.empty()) {
        auto [d, u] = pq.top();
        pq.pop();

        for (const auto& [v, w] : graph[u])
            if (int newDist = d + w; newDist < dist[v]) {
                dist[v] = newDist;
                pq.push({newDist, v});
            }
        }

    return dist;
}

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    int v, e;
    std::cin >> v >> e;

    int k;
    std::cin >> k;

    std::vector<std::vector<std::pair<int, int>>> graph(v);
    for (int i = 0; i < e; ++i) {
        int u, v, w;
        std::cin >> u >> v >> w;

        graph[u - 1].emplace_back(v - 1, w);
    }

    for (const auto i : dijkstra(k - 1, graph))
        if (i == std::numeric_limits<int>::max())
            std::cout << "INF\n";
        else
            std::cout << i << '\n';

    return 0;
}