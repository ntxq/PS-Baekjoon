#include <iostream>
#include <numeric>
#include <vector>

int fourSquares(int n) {
    std::vector<int> dp(n + 1);

    std::iota(dp.begin(), dp.end(), 0);

    for (int i = 0; i <= n; ++i)
        for (int j = 2; j * j <= i; ++j)
            if (dp[i - j * j] + 1 < dp[i]) dp[i] = dp[i - j * j] + 1;

    return dp[n];
}

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    int n;
    std::cin >> n;

    std::cout << fourSquares(n);

    return 0;
}