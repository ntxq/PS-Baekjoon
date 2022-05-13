#include <algorithm>
#include <iostream>

void dfs(int u, std::vector<int>& dist, std::vector<std::vector<int>>& Adj) {
    static int time = 1;
    dist[u] = time++;

    std::sort(Adj[u].begin(), Adj[u].end());

    for (int v : Adj[u])
        if (!dist[v]) dfs(v, dist, Adj);
}

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    int N, M, R;
    std::cin >> N >> M >> R;

    std::vector<std::vector<int>> Adj(N + 1);
    for (int i = 0; i < M; ++i) {
        int u, v;
        std::cin >> u >> v;

        Adj[u].push_back(v);
        Adj[v].push_back(u);
    }

    std::vector<int> dist(N + 1);
    dfs(R, dist, Adj);

    for (int i = 1; i <= N; ++i) std::cout << dist[i] << '\n';

    return 0;
}