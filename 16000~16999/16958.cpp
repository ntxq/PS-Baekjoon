#include <algorithm>
#include <iostream>
#include <limits>
#include <numeric>
#include <vector>

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    int N, T;
    std::cin >> N >> T;

    std::vector<std::tuple<bool, int, int>> cities(N);
    for (auto& [s, x, y] : cities) std::cin >> s >> x >> y;

    std::vector<std::vector<int>> dist(N, std::vector<int>(N));
    for (int i = 0; i < N; ++i) {
        auto [s1, x1, y1] = cities[i];
        for (int j = i + 1; j < N; ++j) {
            auto [s2, x2, y2] = cities[j];

            dist[i][j] = dist[j][i] = std::abs(x1 - x2) + std::abs(y1 - y2);
            if (s1 && s2) dist[i][j] = dist[j][i] = std::min(dist[i][j], T);
        }
    }

    for (int k = 0; k < N; ++k)
        for (int i = 0; i < N; ++i)
            for (int j = 0; j < N; ++j)
                dist[i][j] = std::min(dist[i][j], dist[i][k] + dist[k][j]);

    int M;
    std::cin >> M;

    while (M--) {
        int u, v;
        std::cin >> u >> v;

        std::cout << dist[u - 1][v - 1] << '\n';
    }

    return 0;
}
