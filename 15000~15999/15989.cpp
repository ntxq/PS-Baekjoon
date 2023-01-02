#include <algorithm>
#include <array>
#include <iostream>
#include <limits>
#include <vector>

constexpr std::array<long long, 10001> dp = [] {
    std::array<long long, 10001> dp{};

    dp[0] = 1;
    dp[1] = 1;
    dp[2] = 2;
    dp[3] = 3;

    for (int i = 4; i < 10001; ++i) dp[i] = dp[i - 3] + i / 2 + 1;

    return dp;
}();

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    int T;
    std::cin >> T;
    
    while (T--) {
        int N;
        std::cin >> N;
        std::cout << dp[N] << '\n';
    }

    return 0;
}
