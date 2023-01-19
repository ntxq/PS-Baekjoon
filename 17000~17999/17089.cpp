#include <algorithm>
#include <iostream>
#include <limits>
#include <numeric>
#include <vector>

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    int N, M;
    std::cin >> N >> M;

    std::vector<std::vector<int>> adjList(N);
    std::vector<std::vector<bool>> adjMatrix(N, std::vector<bool>(N));

    for (int i = 0; i < M; ++i) {
        int u, v;
        std::cin >> u >> v;

        adjList[u - 1].push_back(v - 1);
        adjList[v - 1].push_back(u - 1);

        adjMatrix[u - 1][v - 1] = true;
        adjMatrix[v - 1][u - 1] = true;
    }

    for (auto& row : adjList) std::sort(row.begin(), row.end());

    int minCount = std::numeric_limits<int>::max();
    for (int i = 0; i < N; ++i)
        for (int j : adjList[i])
            for (int k : adjList[j])
                if (adjMatrix[k][i])
                    minCount = std::min(
                        minCount,
                        static_cast<int>(adjList[i].size() + adjList[j].size() +
                                         adjList[k].size() - 6));

    if (minCount == std::numeric_limits<int>::max())
        std::cout << -1 << '\n';
    else
        std::cout << minCount << '\n';

    return 0;
}