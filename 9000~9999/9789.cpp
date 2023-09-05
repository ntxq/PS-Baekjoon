#include <algorithm>
#include <bitset>
#include <iostream>
#include <vector>

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    int V, E;
    std::cin >> V >> E;

    std::vector<std::bitset<2000>> dist(V, std::bitset<2000>());
    for (int i = 0; i < V; ++i) dist[i][i] = true;

    for (int i = 0; i < E; ++i) {
        int u, v;
        std::cin >> u >> v;

        dist[u][v] = true;
    }

    for (int i = 0; i < V; ++i)
        for (int j = 0; j < V; ++j)
            if (dist[j][i]) dist[j] |= dist[i];

    int Q;
    std::cin >> Q;

    for (int i = 0; i < Q; ++i) {
        int u, v;
        std::cin >> u >> v;

        std::cout << dist[u][v] << '\n';
    }

    return 0;
}
