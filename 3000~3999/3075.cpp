#include <algorithm>
#include <iostream>
#include <limits>
#include <vector>

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    int T;
    std::cin >> T;

    while (T--) {
        int N, P, Q;
        std::cin >> N >> P >> Q;

        std::vector<int> S(N);
        for (int& s : S) std::cin >> s;

        std::vector<std::vector<int>> dist(
            P, std::vector<int>(P, std::numeric_limits<int>::max()));
        for (int i = 0; i < Q; ++i) {
            int u, v, w;
            std::cin >> u >> v >> w;

            dist[u - 1][v - 1] = std::min(dist[u - 1][v - 1], w);
            dist[v - 1][u - 1] = std::min(dist[v - 1][u - 1], w);
        }

        for (int i = 0; i < P; ++i) dist[i][i] = 0;

        for (int k = 0; k < P; ++k)
            for (int i = 0; i < P; ++i)
                for (int j = 0; j < P; ++j)
                    if (dist[i][k] != std::numeric_limits<int>::max() &&
                        dist[k][j] != std::numeric_limits<int>::max())
                        dist[i][j] =
                            std::min(dist[i][j], dist[i][k] + dist[k][j]);

        std::vector<unsigned long long> costs(P);
        for (int t = 0; t < P; ++t)
            for (int s : S) {
                if (dist[s - 1][t] == std::numeric_limits<int>::max()) {
                    costs[t] = std::numeric_limits<int>::max();
                    break;
                }

                costs[t] += static_cast<unsigned long long>(dist[s - 1][t]) *
                            static_cast<unsigned long long>(dist[s - 1][t]);
            }

        auto min_cost = std::min_element(costs.begin(), costs.end());
        std::cout << std::distance(costs.begin(), min_cost) + 1 << ' '
                  << *min_cost << '\n';
    }

    return 0;
}
