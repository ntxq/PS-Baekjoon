#include <algorithm>
#include <iomanip>
#include <iostream>
#include <limits>
#include <vector>

struct Edge {
    int from;
    int to;
    int weight;
};

constexpr int INF = std::numeric_limits<int>::max();

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    int N, M;
    std::cin >> N >> M;

    std::vector<Edge> edges(M);
    std::vector<std::vector<int>> graph(N + 1, std::vector<int>(N + 1, INF));

    for (int i = 0; i < M; ++i) {
        std::cin >> edges[i].from >> edges[i].to >> edges[i].weight;
        graph[edges[i].from][edges[i].to] =
            std::min(graph[edges[i].from][edges[i].to], edges[i].weight);
        graph[edges[i].to][edges[i].from] =
            std::min(graph[edges[i].to][edges[i].from], edges[i].weight);
    }

    for (int i = 1; i <= N; ++i) graph[i][i] = 0;

    for (int k = 1; k <= N; ++k)
        for (int i = 1; i <= N; ++i)
            for (int j = 1; j <= N; ++j)
                if (graph[i][k] && graph[k][j] && graph[i][k] != INF &&
                    graph[k][j] != INF)
                    graph[i][j] =
                        std::min(graph[i][j], graph[i][k] + graph[k][j]);

    int minTime = INF;
    for (int i = 1; i <= N; ++i) {
        int maxTime = 0;
        for (int j = 0; j < M; ++j)
            maxTime =
                std::max(maxTime, graph[i][edges[j].from] +
                                      graph[i][edges[j].to] + edges[j].weight);
        minTime = std::min(minTime, maxTime);
    }

    std::cout << std::fixed << std::showpoint << std::setprecision(1)
              << static_cast<double>(minTime) / 2.0 << '\n';

    return 0;
}