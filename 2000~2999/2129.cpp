#include <algorithm>
#include <iostream>
#include <limits>
#include <queue>
#include <vector>

std::pair<int, int> operator+(const std::pair<int, int>& lhs,
                              const std::pair<int, int>& rhs) {
    return {lhs.first + rhs.first, lhs.second + rhs.second};
}

bool operator>(const std::pair<int, int>& lhs, const std::pair<int, int>& rhs) {
    return lhs.first > rhs.first ||
           (lhs.first == rhs.first && lhs.second > rhs.second);
}

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    int N, M, S, T;
    std::cin >> N >> M >> S >> T;

    std::vector<std::vector<std::tuple<int, int, int>>> adj(N);
    for (int i = 0; i < M; ++i) {
        int u, v, a, w, b;
        std::cin >> u >> v >> a >> w >> b;
        adj[u].push_back({a, w, v});
        adj[v].push_back({b, w, u});
    }

    for (int i = 0; i < N; ++i) {
        std::sort(adj[i].begin(), adj[i].end());
        while (!adj[i].empty() &&
               std::get<0>(adj[i].back()) > std::get<0>(adj[i].front()))
            adj[i].pop_back();
    }

    std::vector<std::pair<int, int>> dist(
        N, {std::numeric_limits<int>::max(), std::numeric_limits<int>::max()});
    dist[S] = {0, 0};

    for (int i = 0; i < N - 1; ++i)
        for (int u = 0; u < N; ++u)
            if (dist[u].first != std::numeric_limits<int>::max())
                for (auto [a, w, v] : adj[u])
                    if (dist[v] > (dist[u] + std::pair<int, int>{a, w}))
                        dist[v] = dist[u] + std::pair<int, int>{a, w};

    std::vector<bool> is_negative_cycle(N, false);
    for (int u = 0; u < N; ++u)
        if (dist[u].first != std::numeric_limits<int>::max())
            for (auto [a, w, v] : adj[u])
                if (dist[v] > (dist[u] + std::pair<int, int>{a, w})) {
                    dist[v] = dist[u] + std::pair<int, int>{a, w};
                    is_negative_cycle[v] = true;
                }

    std::queue<int> q;
    for (int i = 0; i < N; ++i)
        if (is_negative_cycle[i]) q.push(i);
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (auto [a, w, v] : adj[u])
            if (!is_negative_cycle[v]) {
                is_negative_cycle[v] = true;
                q.push(v);
            }
    }

    if (dist[T].second == std::numeric_limits<int>::max())
        std::cout << "VOID\n";
    else if (is_negative_cycle[T])
        std::cout << "UNBOUND\n";
    else
        std::cout << dist[T].first << ' ' << dist[T].second << '\n';

    return 0;
}
