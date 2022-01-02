#include <algorithm>
#include <iostream>
#include <vector>

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    int n;
    std::cin >> n;

    std::vector<std::vector<int>> prices(n, std::vector<int>(3));
    for (int i = 0; i < n; ++i)
        std::cin >> prices[i][0] >> prices[i][1] >> prices[i][2];

    std::vector<std::vector<int>> dp(n, std::vector<int>(3));
    dp[0] = prices[0];

    for (int i = 1; i < n; ++i) {
        dp[i][0] =
            std::min(dp[i - 1][1] + prices[i][0], dp[i - 1][2] + prices[i][0]);
        dp[i][1] =
            std::min(dp[i - 1][0] + prices[i][1], dp[i - 1][2] + prices[i][1]);
        dp[i][2] =
            std::min(dp[i - 1][0] + prices[i][2], dp[i - 1][1] + prices[i][2]);
    }

    std::cout << std::min({dp[n - 1][0], dp[n - 1][1], dp[n - 1][2]});

    return 0;
}