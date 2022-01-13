#include <algorithm>
#include <iostream>
#include <limits>
#include <numeric>
#include <vector>

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    int n, m;
    std::cin >> n >> m;

    const int& maxInt = std::numeric_limits<int>::max();

    std::vector<std::vector<int>> dist(n, std::vector<int>(n, maxInt));
    for (int i = 0; i < m; ++i) {
        int u, v;
        std::cin >> u >> v;

        dist[u - 1][v - 1] = 1;
        dist[v - 1][u - 1] = 1;
    }

    for (int i = 0; i < n; ++i) dist[i][i] = 0;

    for (int k = 0; k < n; ++k)
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < n; ++j)
                if (int newDist = dist[i][k] + dist[k][j];
                    dist[i][k] != maxInt && dist[k][j] != maxInt &&
                    newDist < dist[i][j])
                    dist[i][j] = newDist;

    int index = 0;
    for (int i = 0, minCount = maxInt; i < n; ++i) {
        int count = std::reduce(dist[i].cbegin(), dist[i].cend());
        if (count < minCount) {
            minCount = count;
            index = i;
        }
    }

    std::cout << index + 1;

    return 0;
}