#include <iostream>
#include <limits>
#include <utility>
#include <vector>

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    int n, m, r;
    std::cin >> n >> m >> r;

    std::vector<int> items(n);
    for (int& i : items) std::cin >> i;

    const int MAX = std::numeric_limits<int>::max();
    std::vector<std::vector<int>> dist(n, std::vector<int>(n, MAX));
    for (int i = 0; i < n; ++i) dist[i][i] = 0;

    for (int i = 0; i < r; ++i) {
        int u, v, w;
        std::cin >> u >> v >> w;

        if (w < dist[u - 1][v - 1]) dist[u - 1][v - 1] = dist[v - 1][u - 1] = w;
    }

    for (int k = 0; k < n; ++k)
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < n; ++j)
                if (int d = dist[i][k] + dist[k][j];
                    dist[i][k] != MAX && dist[k][j] != MAX && d < dist[i][j])
                    dist[i][j] = d;

    int maxItems = 0;
    for (const auto& u : dist) {
        int curItems = 0;
        for (int v = 0; v < n; ++v)
            if (u[v] <= m) curItems += items[v];

        if (curItems > maxItems) maxItems = curItems;
    }

    std::cout << maxItems;

    return 0;
}