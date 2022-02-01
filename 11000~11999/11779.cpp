#include <iostream>
#include <limits>
#include <queue>
#include <stack>
#include <vector>

void dijkstra(const std::vector<std::vector<std::pair<int, int>>>& adj, int s,
              int t) {
    std::vector<unsigned long long> dist(
        adj.size(), std::numeric_limits<unsigned long long>::max());
    std::vector<int> prev(adj.size());
    std::priority_queue<std::pair<unsigned long long, int>,
                        std::vector<std::pair<unsigned long long, int>>,
                        std::greater<std::pair<unsigned long long, int>>>
        pq;

    dist[s] = 0;
    pq.push({0, s});

    while (!pq.empty()) {
        auto [d, u] = pq.top();
        pq.pop();

        if (d == dist[u])
            for (const auto& [v, w] : adj[u])
                if (unsigned long long newD = d + w; newD < dist[v]) {
                    dist[v] = newD;
                    prev[v] = u;
                    pq.push({newD, v});
                }
    }

    std::stack<int> path;
    for (int u = t; u != s; u = prev[u]) path.push(u);
    path.push(s);

    std::cout << dist[t] << '\n' << path.size() << '\n';
    while (!path.empty()) {
        std::cout << path.top() + 1 << ' ';
        path.pop();
    }
}

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    int n, m;
    std::cin >> n >> m;

    std::vector<std::vector<std::pair<int, int>>> adj(n);
    for (int i = 0; i < m; ++i) {
        int u, v, w;
        std::cin >> u >> v >> w;

        adj[u - 1].push_back({v - 1, w});
    }
    int s, t;
    std::cin >> s >> t;

    dijkstra(adj, s - 1, t - 1);

    return 0;
}