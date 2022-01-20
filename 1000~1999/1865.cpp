#include <algorithm>
#include <iostream>
#include <limits>
#include <tuple>
#include <vector>

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    int tc;
    std::cin >> tc;

    for (int i = 0; i < tc; ++i) {
        int n, m, w;
        std::cin >> n >> m >> w;

        std::vector<int> dist(n + 1);
        std::vector<std::tuple<int, int, int>> edges;

        for (int j = 0; j < m; ++j) {
            int s, e, t;
            std::cin >> s >> e >> t;

            edges.push_back({s, e, t});
            edges.push_back({e, s, t});
        }

        for (int j = 0; j < w; ++j) {
            int s, e, t;
            std::cin >> s >> e >> t;

            edges.push_back({s, e, -t});
        }

        for (int j = 0; j < n - 1; ++j)
            for (const auto& [u, v, w] : edges)
                if (int curDist = dist[u] + w; curDist < dist[v])
                    dist[v] = curDist;

        bool isNegativeCycle = false;
        for (const auto& [u, v, w] : edges)
            if (dist[u] + w < dist[v]) isNegativeCycle = true;

        std::cout << (isNegativeCycle ? "YES" : "NO") << '\n';
    }

    return 0;
}