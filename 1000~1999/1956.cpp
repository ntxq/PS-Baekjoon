#include <algorithm>
#include <iostream>
#include <limits>
#include <utility>
#include <vector>

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    const int INF = std::numeric_limits<int>::max();

    int V, E;
    std::cin >> V >> E;

    std::vector<std::vector<int>> dist(V + 1, std::vector<int>(V + 1, INF));
    for (int i = 0; i < E; ++i) {
        int a, b, c;
        std::cin >> a >> b >> c;

        dist[a][b] = c;
    }

    for (int k = 1; k <= V; ++k)
        for (int i = 1; i <= V; ++i)
            for (int j = 1; j <= V; ++j)
                if (dist[i][k] != INF && dist[k][j] != INF &&
                    dist[i][k] + dist[k][j] < dist[i][j])
                    dist[i][j] = dist[i][k] + dist[k][j];

    int minCycle = INF;
    for (int i = 1; i <= V; ++i)
        if (dist[i][i] < minCycle) minCycle = dist[i][i];

    std::cout << (minCycle == INF ? -1 : minCycle) << '\n';

    return 0;
}