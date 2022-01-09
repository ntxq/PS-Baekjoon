#include <iostream>
#include <limits>
#include <vector>

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    const int& maxInt = std::numeric_limits<int>::max();

    int n, m;
    std::cin >> n >> m;

    std::vector<std::vector<int>> dist(n, std::vector<int>(n, maxInt));

    for (int i = 0; i < m; ++i) {
        int a, b, c;
        std::cin >> a >> b >> c;

        if (dist[a - 1][b - 1] > c) dist[a - 1][b - 1] = c;
    }

    for (int i = 0; i < n; ++i) dist[i][i] = 0;

    for (int k = 0; k < n; ++k)
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < n; ++j)
                if (int newDist = dist[i][k] + dist[k][j];
                    dist[i][k] != maxInt && dist[k][j] != maxInt &&
                    dist[i][j] > newDist)
                    dist[i][j] = newDist;

    for (const auto& row : dist) {
        for (const auto& elem : row)
            std::cout << (elem == maxInt ? 0 : elem) << ' ';
        std::cout << '\n';
    }

    return 0;
}