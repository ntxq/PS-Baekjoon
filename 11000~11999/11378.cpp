#include <algorithm>
#include <iostream>
#include <queue>
#include <vector>

bool bfs(int s, int t, const std::vector<std::vector<int>>& adj,
         const std::vector<std::vector<int>>& capacity,
         std::vector<int>& parent) {
    std::queue<int> q;
    std::fill(parent.begin(), parent.end(), -1);

    q.push(s);
    parent[s] = s;

    while (!q.empty() && parent[t] == -1) {
        int u = q.front();
        q.pop();

        for (int v : adj[u])
            if (parent[v] == -1 && capacity[u][v]) {
                parent[v] = u;
                q.push(v);
            }
    }

    return parent[t] != -1;
}

int maxflow(int s, int t, const std::vector<std::vector<int>>& adj,
            std::vector<std::vector<int>>& capacity) {
    int flow = 0;

    std::vector<int> parent(adj.size());
    while (bfs(s, t, adj, capacity, parent)) {
        ++flow;

        int cur = t;
        while (cur != parent[cur]) {
            int prev = parent[cur];

            --capacity[prev][cur];
            ++capacity[cur][prev];

            cur = prev;
        }
    }

    return flow;
}

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    int N, M, K;
    std::cin >> N >> M >> K;

    std::vector<std::vector<int>> adj(N + M + 3);
    std::vector<std::vector<int>> capacity(N + M + 3,
                                           std::vector<int>(N + M + 3));

    adj[0].push_back(N + M + 1);
    adj[N + M + 1].push_back(0);
    capacity[0][N + M + 1] = K;

    for (int i = 1; i <= N; ++i) {
        int cnt;
        std::cin >> cnt;

        for (int j = 0; j < cnt; ++j) {
            int w;
            std::cin >> w;

            adj[i].push_back(N + w);
            adj[N + w].push_back(i);
            capacity[i][N + w] = 1;
        }

        adj[0].push_back(i);
        adj[i].push_back(0);
        capacity[0][i] = 1;

        adj[N + M + 1].push_back(i);
        adj[i].push_back(N + M + 1);
        capacity[N + M + 1][i] = K;
    }

    for (int i = N + 1; i <= N + M; ++i) {
        adj[i].push_back(N + M + 2);
        adj[N + M + 2].push_back(i);
        capacity[i][N + M + 2] = 1;
    }

    std::cout << maxflow(0, N + M + 2, adj, capacity) << '\n';

    return 0;
}