#include <algorithm>
#include <iostream>
#include <limits>
#include <vector>

/*
Subproblem
Relation
Topological Order
Base Case
Original Problem
Time Complexity
*/

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    int N, K;
    std::cin >> N >> K;

    std::vector<int> coins(N);
    for (auto& coin : coins) std::cin >> coin;

    std::vector<int> dp(K + 1, std::numeric_limits<int>::max());

    dp[0] = 0;
    for (int i = 1; i < K + 1; ++i)
        for (const auto& coin : coins)
            if (int prev = i - coin;
                prev >= 0 && dp[prev] != std::numeric_limits<int>::max() &&
                dp[prev] + 1 < dp[i])
                dp[i] = dp[prev] + 1;

    std::cout << (dp[K] == std::numeric_limits<int>::max() ? -1 : dp[K])
              << '\n';

    return 0;
}
