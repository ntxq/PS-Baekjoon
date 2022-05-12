#include <algorithm>
#include <iostream>
#include <queue>
#include <vector>

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    int T;
    std::cin >> T;

    while (T--) {
        int N;
        std::cin >> N;

        std::vector<int> prevRanks(N);
        for (int& rank : prevRanks) std::cin >> rank;

        std::vector<std::vector<bool>> adj(N + 1, std::vector<bool>(N + 1));
        for (int i = 0; i < N; ++i)
            for (int j = i + 1; j < N; ++j)
                adj[prevRanks[i]][prevRanks[j]] = true;

        int M;
        std::cin >> M;

        for (int i = 0; i < M; ++i) {
            int u, v;
            std::cin >> u >> v;

            std::swap(adj[u][v], adj[v][u]);
        }

        std::vector<int> inDegree(N + 1);
        for (int i = 1; i <= N; ++i)
            for (int j = 1; j <= N; ++j)
                if (adj[i][j]) ++inDegree[j];

        std::queue<int> q;
        for (int i = 1; i <= N; ++i)
            if (!inDegree[i]) q.push(i);

        std::vector<int> order;
        bool isUnique = q.size() == 1;

        while (!q.empty() && isUnique) {
            int u = q.front();
            q.pop();

            isUnique = q.empty();

            order.push_back(u);
            for (int v = 1; v <= N; ++v)
                if (adj[u][v]) {
                    --inDegree[v];
                    if (!inDegree[v]) q.push(v);
                }
        }

        if (order.size() != static_cast<unsigned>(N))
            std::cout << "IMPOSSIBLE";
        else if (!isUnique)
            std::cout << "?";
        else
            for (const auto& u : order) std::cout << u << " ";
        std::cout << "\n";
    }

    return 0;
}