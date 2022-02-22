#include <algorithm>
#include <iostream>
#include <limits>
#include <vector>

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    int n;
    std::cin >> n;

    std::vector<std::vector<int>> costs(n, std::vector<int>(3));
    for (auto& color : costs) std::cin >> color[0] >> color[1] >> color[2];

    std::vector<std::vector<std::vector<int>>> dp(
        3, std::vector<std::vector<int>>(
               n, std::vector<int>(3, std::numeric_limits<int>::max())));

    for (int i = 0; i < 3; ++i) {
        dp[i][0][i] = costs[0][i];

        for (int j = 1; j < n; ++j) {
            dp[i][j][0] =
                std::min(dp[i][j - 1][1], dp[i][j - 1][2]) + costs[j][0];
            dp[i][j][1] =
                std::min(dp[i][j - 1][0], dp[i][j - 1][2]) + costs[j][1];
            dp[i][j][2] =
                std::min(dp[i][j - 1][0], dp[i][j - 1][1]) + costs[j][2];

            if (j == 1 || j == n - 1)
                dp[i][j][i] = std::numeric_limits<int>::max();
        }
    }

    int minCost = std::numeric_limits<int>::max();
    for (int i = 0; i < 3; ++i)
        if (int curMin =
                *std::min_element(dp[i][n - 1].cbegin(), dp[i][n - 1].cend());
            curMin < minCost)
            minCost = curMin;

    std::cout << minCost << '\n';

    return 0;
}
