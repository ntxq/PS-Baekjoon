#include <algorithm>
#include <array>
#include <iostream>
#include <limits>
#include <vector>

constexpr int TABLE_SIZE = 101;

constexpr std::array<long long, TABLE_SIZE> DP = [] {
    std::array<long long, TABLE_SIZE> dp{};

    dp[0] = 0;
    for (int i = 1; i < TABLE_SIZE; ++i) {
        dp[i] = dp[i - 1] + 1;
        for (int j = 3; j < i; ++j)
            if (dp[i] < dp[i - j] * (j - 1)) dp[i] = dp[i - j] * (j - 1);
    }

    return dp;
}();

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    int N;
    std::cin >> N;

    std::cout << DP[N] << '\n';

    return 0;
}
