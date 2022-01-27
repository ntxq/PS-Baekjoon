#include <algorithm>
#include <iostream>
#include <limits>
#include <queue>
#include <vector>

typedef std::vector<std::vector<std::pair<int, int>>> Graph;

std::pair<int, int> dijkstra(const Graph& g, int start, int t1, int t2) {
    const int INF = std::numeric_limits<int>::max();

    std::vector<int> dist(g.size(), INF);
    std::priority_queue<std::pair<int, int>> q;

    q.push({0, start});
    dist[start] = 0;

    while (!q.empty()) {
        auto [d, v] = q.top();
        q.pop();

        for (const auto& [u, w] : g[v])
            if (int newDist = d + w; newDist < dist[u]) {
                dist[u] = newDist;
                q.push({newDist, u});
            }
    }

    if (dist[t1] == INF) dist[t1] = -1;
    if (dist[t2] == INF) dist[t2] = -1;

    return {dist[t1], dist[t2]};
}

int shortestDist(const Graph& g, int start, int v1, int v2, int end) {
    auto [d1, d2] = dijkstra(g, start, v1, v2);

    auto [d3, d4] = dijkstra(g, end, v1, v2);

    if (d1 == -1 || d2 == -1 || d3 == -1 || d4 == -1) return -1;

    return std::min(d1 + d4, d2 + d3) + dijkstra(g, v1, v2, v2).first;
}

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    int n, e;
    std::cin >> n >> e;

    Graph g(n);
    for (int i = 0; i < e; ++i) {
        int a, b, c;
        std::cin >> a >> b >> c;

        g[a - 1].push_back({b - 1, c});
        g[b - 1].push_back({a - 1, c});
    }

    int v1, v2;
    std::cin >> v1 >> v2;

    std::cout << shortestDist(g, 0, v1 - 1, v2 - 1, n - 1);

    return 0;
}