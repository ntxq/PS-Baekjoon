#include <algorithm>
#include <array>
#include <iostream>
#include <limits>
#include <numeric>
#include <string>
#include <vector>

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    int L, K;
    std::cin >> L >> K;

    std::vector<std::array<unsigned long long, 2>> dp(L + 1);
    dp[0][1] = 1;

    for (int l = 1; l <= L; ++l) {
        dp[l][0] = dp[l - 1][1] + (l >= K ? dp[l - K][1] : 0);
        dp[l][1] = dp[l - 1][0];
    }

    std::cout << std::accumulate(
                     dp.begin(), dp.end(), 0ULL,
                     [](unsigned long long acc,
                        const std::array<unsigned long long, 2>& a) {
                         return acc + a[0];
                     })
              << '\n';

    return 0;
}
