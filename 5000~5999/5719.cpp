#include <algorithm>
#include <iostream>
#include <limits>
#include <queue>
#include <vector>

void dijkstra(int s, std::vector<int>& dist,
              std::vector<std::vector<std::pair<int, int>>>& prev,
              const std::vector<std::vector<std::pair<int, int>>>& graph) {
    std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>,
                        std::greater<std::pair<int, int>>>
        pq;

    dist[s] = 0;
    pq.push({0, s});

    while (!pq.empty()) {
        auto [d, u] = pq.top();
        pq.pop();

        if (dist[u] < d) continue;

        for (unsigned i = 0; i < graph[u].size(); ++i) {
            auto [v, w] = graph[u][i];
            if (dist[v] > d + w && w != -1) {
                dist[v] = d + w;
                prev[v] = {{u, i}};
                pq.push({dist[v], v});
            } else if (dist[v] == d + w && w != -1) {
                prev[v].push_back({u, i});
            }
        }
    }
}

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    int n, m;
    while (std::cin >> n >> m && n && m) {
        int s, d;
        std::cin >> s >> d;

        std::vector<std::vector<std::pair<int, int>>> graph(n);
        for (int i = 0; i < m; ++i) {
            int u, v, w;
            std::cin >> u >> v >> w;

            graph[u].push_back({v, w});
        }

        std::vector<int> dist(n, std::numeric_limits<int>::max());
        std::vector<std::vector<std::pair<int, int>>> prev(n);

        dijkstra(s, dist, prev, graph);

        std::queue<int> q;
        std::vector<bool> visited(n);

        q.push(d);
        while (!q.empty()) {
            int cur = q.front();
            q.pop();

            for (auto [p, i] : prev[cur]) {
                if (!visited[p]) {
                    visited[p] = true;
                    q.push(p);
                }

                graph[p][i].second = -1;
            }
        }

        dist.assign(n, std::numeric_limits<int>::max());
        prev.assign(n, {});
        dijkstra(s, dist, prev, graph);

        std::cout << (dist[d] == std::numeric_limits<int>::max() ? -1 : dist[d])
                  << '\n';
    }

    return 0;
}
