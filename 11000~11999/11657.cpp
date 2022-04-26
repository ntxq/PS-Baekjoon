#include <algorithm>
#include <iostream>
#include <limits>
#include <utility>
#include <vector>

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    int N, M;
    std::cin >> N >> M;

    std::vector<std::vector<std::pair<int, int>>> graph(N + 1);
    for (int i = 0; i < M; ++i) {
        int A, B, C;
        std::cin >> A >> B >> C;

        graph[A].push_back({B, C});
    }

    std::vector<long long> dist(N + 1, std::numeric_limits<long long>::max());
    dist[1] = 0;

    for (int i = 0; i < N - 1; ++i)
        for (int u = 1; u <= N; ++u)
            for (auto [v, w] : graph[u])
                if (dist[u] != std::numeric_limits<long long>::max() &&
                    dist[u] + w < dist[v])
                    dist[v] = dist[u] + w;

    bool isNegativeCycle = false;
    for (int u = 1; u <= N && !isNegativeCycle; ++u)
        for (auto [v, w] : graph[u])
            if (dist[u] != std::numeric_limits<long long>::max() &&
                dist[u] + w < dist[v])
                isNegativeCycle = true;

    if (isNegativeCycle)
        std::cout << -1 << '\n';
    else
        for (int v = 2; v <= N; ++v)
            if (dist[v] == std::numeric_limits<long long>::max())
                std::cout << -1 << '\n';
            else
                std::cout << dist[v] << '\n';

    return 0;
}