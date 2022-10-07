#include <algorithm>
#include <iostream>
#include <vector>

std::vector<int> ants;

std::vector<std::vector<std::pair<int, long long>>> parent;
std::vector<bool> visited;
std::vector<std::vector<std::pair<int, int>>> adj;

void dfs(int u) {
    visited[u] = true;
    for (auto [v, w] : adj[u])
        if (!visited[v]) {
            parent[v][0] = {u, w};
            dfs(v);
        }
}

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    int N;
    std::cin >> N;

    ants.resize(N);
    for (auto& i : ants) std::cin >> i;

    adj.resize(N + 1);
    for (int i = 0; i < N - 1; ++i) {
        int u, v, w;
        std::cin >> u >> v >> w;

        adj[u].push_back({v, w});
        adj[v].push_back({u, w});
    }

    parent.assign(N + 1, std::vector<std::pair<int, long long>>(18));
    visited.resize(N + 1, false);
    dfs(1);

    for (int j = 1; j < 18; ++j)
        for (int i = 1; i <= N; ++i)
            parent[i][j] = {parent[parent[i][j - 1].first][j - 1].first,
                            parent[i][j - 1].second +
                                parent[parent[i][j - 1].first][j - 1].second};

    for (int i = 1; i <= N; ++i) {
        int energy = ants[i - 1];
        int current = i;

        for (int j = 17; j >= 0; --j)
            if (parent[current][j].first != 0 &&
                parent[current][j].second <= energy) {
                energy -= parent[current][j].second;
                current = parent[current][j].first;
            }

        std::cout << current << '\n';
    }

    return 0;
}