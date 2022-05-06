#include <algorithm>
#include <bitset>
#include <cmath>
#include <iostream>
#include <limits>

int dfs(int x, int visited, std::vector<std::vector<int>>& dp,
        const std::vector<std::vector<int>>& cost, int N) {
    if (visited == (1 << N) - 1) return 0;

    if (dp[x][visited] != std::numeric_limits<int>::max())
        return dp[x][visited];

    for (int i = 0; i < N; ++i)
        if (!(visited & (1 << i)))
            dp[x][visited] = std::min(
                dp[x][visited],
                dfs(x + 1, visited | (1 << i), dp, cost, N) + cost[x][i]);

    return dp[x][visited];
}

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    int N;
    std::cin >> N;

    std::vector<std::vector<int>> cost(N, std::vector<int>(N));
    for (auto& row : cost)
        for (auto& col : row) std::cin >> col;

    std::vector<std::vector<int>> dp(
        N, std::vector<int>(1 << (N + 1), std::numeric_limits<int>::max()));

    std::cout << dfs(0, 0, dp, cost, N) << '\n';

    return 0;
}