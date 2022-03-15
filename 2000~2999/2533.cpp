#include <algorithm>
#include <array>
#include <iostream>
#include <vector>

void visit(int x, std::vector<std::array<int, 2>>& dp,
           std::vector<bool>& visited,
           const std::vector<std::vector<int>>& sns) {
    visited[x] = true;
    dp[x][0] = 1;

    for (const auto& child : sns[x]) {
        if (!visited[child]) {
            visit(child, dp, visited, sns);
            dp[x][0] += std::min(dp[child][0], dp[child][1]);
            dp[x][1] += dp[child][0];
        }
    }
}

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    int n;
    std::cin >> n;

    std::vector<std::vector<int>> sns(n);
    for (int i = 0; i < n - 1; ++i) {
        int u, v;
        std::cin >> u >> v;

        sns[u - 1].push_back(v - 1);
        sns[v - 1].push_back(u - 1);
    }

    std::vector<std::array<int, 2>> dp(n, {0, 0});
    std::vector<bool> visited(n);
    visit(0, dp, visited, sns);

    std::cout << std::min(dp[0][0], dp[0][1]) << '\n';

    return 0;
}
