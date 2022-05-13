#include <algorithm>
#include <functional>
#include <iostream>
#include <queue>

void bfs(int u, std::vector<int>& dist, std::vector<std::vector<int>>& Adj) {
    static int timer = 0;

    std::queue<int> q;

    dist[u] = ++timer;
    q.push(u);

    while (!q.empty()) {
        int u = q.front();
        q.pop();

        std::sort(Adj[u].begin(), Adj[u].end(), std::greater<int>());
        for (int v : Adj[u])
            if (!dist[v]) {
                dist[v] = ++timer;
                q.push(v);
            }
    }
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
    bfs(R, dist, Adj);

    for (int i = 1; i <= N; ++i) std::cout << dist[i] << '\n';

    return 0;
}