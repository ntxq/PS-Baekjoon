#include <algorithm>
#include <iostream>
#include <limits>
#include <queue>
#include <vector>

void bfs(std::vector<std::vector<int>>& dp,
         const std::vector<std::vector<int>>& adj, const int& N) {
    std::queue<std::pair<int, int>> Q;
    Q.push({0, 1});

    while (!Q.empty()) {
        auto [u, state] = Q.front();
        Q.pop();

        for (int v = 1; v < N; ++v)
            if (!(state & (1 << v)) && adj[u][v] &&
                (dp[u][state] + adj[u][v] < dp[v][state | (1 << v)] ||
                 !dp[v][state | (1 << v)])) {
                dp[v][state | (1 << v)] = dp[u][state] + adj[u][v];
                Q.push({v, state | (1 << v)});
            }
    }
}

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    int N;
    std::cin >> N;

    std::vector<std::vector<int>> adj(N, std::vector<int>(N));
    for (int i = 0; i < N; ++i)
        for (int j = 0; j < N; ++j) std::cin >> adj[i][j];

    std::vector<std::vector<int>> dp(N, std::vector<int>(1 << N));
    bfs(dp, adj, N);

    int minDist = std::numeric_limits<int>::max();
    for (int i = 1; i < N; ++i)
        if (dp[i][(1 << N) - 1] + adj[i][0] < minDist && dp[i][(1 << N) - 1] &&
            adj[i][0])
            minDist = dp[i][(1 << N) - 1] + adj[i][0];

    std::cout << minDist << '\n';

    return 0;
}