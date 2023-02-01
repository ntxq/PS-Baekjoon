#include <algorithm>
#include <iostream>
#include <limits>
#include <numeric>
#include <vector>

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    std::vector<std::vector<long long>> dist(
        8, std::vector<long long>(8, std::numeric_limits<long long>::max()));
    for (int i = 0; i < 8; ++i) dist[i][i] = 0;

    int xs, ys;
    int xe, ye;
    std::cin >> xs >> ys >> xe >> ye;
    dist[0][7] = dist[7][0] = std::abs(xs - xe) + std::abs(ys - ye);

    std::vector<std::pair<int, int>> teleports(6);
    for (auto& [x, y] : teleports) std::cin >> x >> y;
    for (int i = 0; i < 6; ++i) {
        auto [x1, y1] = teleports[i];

        dist[0][i + 1] = dist[i + 1][0] = std::abs(xs - x1) + std::abs(ys - y1);
        dist[7][i + 1] = dist[i + 1][7] = std::abs(xe - x1) + std::abs(ye - y1);

        for (int j = i + 1; j < 6; ++j) {
            auto [x2, y2] = teleports[j];
            dist[i + 1][j + 1] = dist[j + 1][i + 1] =
                std::abs(x1 - x2) + std::abs(y1 - y2);
        }
    }
    for (int i = 0; i < 3; ++i)
        dist[i * 2 + 1][i * 2 + 2] = dist[i * 2 + 2][i * 2 + 1] = 10;

    for (int k = 0; k < 8; ++k)
        for (int i = 0; i < 8; ++i)
            for (int j = 0; j < 8; ++j)
                if (dist[i][k] != std::numeric_limits<long long>::max() &&
                    dist[k][j] != std::numeric_limits<long long>::max())
                    dist[i][j] = std::min(dist[i][j], dist[i][k] + dist[k][j]);

    std::cout << dist[0][7] << '\n';

    return 0;
}
