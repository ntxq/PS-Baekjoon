#include <algorithm>
#include <iostream>
#include <vector>

typedef std::vector<int> Row;
typedef std::vector<Row> Matrix;

void dfs(int u, int p, Matrix& dp, const Matrix& adj, const Row& weights) {
    dp[u][0] = 0;
    dp[u][1] = weights[u];

    for (int v : adj[u])
        if (v != p) {
            dfs(v, u, dp, adj, weights);
            dp[u][0] += std::max(dp[v][0], dp[v][1]);
            dp[u][1] += dp[v][0];
        }
}

void trace(int u, int p, std::vector<bool>& path, const Matrix& dp,
           const Matrix& adj) {
    if (dp[u][0] < dp[u][1] && !path[p]) path[u] = true;

    for (int v : adj[u])
        if (v != p) trace(v, u, path, dp, adj);
}

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    int N;
    std::cin >> N;

    Row weights(N + 1);
    for (int i = 1; i <= N; ++i) std::cin >> weights[i];

    Matrix adj(N + 1);
    for (int i = 0; i < N - 1; ++i) {
        int u, v;
        std::cin >> u >> v;

        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    Matrix dp(N + 1, Row(2, 0));
    dfs(1, 0, dp, adj, weights);

    std::cout << std::max(dp[1][0], dp[1][1]) << '\n';

    std::vector<bool> path(N + 1);
    trace(1, 0, path, dp, adj);

    for (int i = 1; i <= N; ++i)
        if (path[i]) std::cout << i << ' ';

    return 0;
}