#include <algorithm>
#include <iostream>
#include <limits>
#include <numeric>
#include <vector>

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    int N;
    std::cin >> N;

    std::vector<int> cows(N);
    for (auto& cow : cows) std::cin >> cow;

    std::vector<std::vector<int>> dp(N, std::vector<int>(3, 0));
    dp[0][0] = cows[0] != 1;
    dp[0][1] = cows[0] != 2;
    dp[0][2] = cows[0] != 3;

    std::vector<std::vector<int>> rev_dp(N, std::vector<int>(3, 0));
    rev_dp[0][0] = cows[0] != 1;
    rev_dp[0][1] = cows[0] != 2;
    rev_dp[0][2] = cows[0] != 3;

    for (int i = 1; i < N; ++i) {
        dp[i][0] = dp[i - 1][0] + (cows[i] != 1);
        dp[i][1] = std::min(dp[i - 1][0], dp[i - 1][1]) + (cows[i] != 2);
        dp[i][2] = std::min({dp[i - 1][0], dp[i - 1][1], dp[i - 1][2]}) +
                   (cows[i] != 3);

        rev_dp[i][2] = rev_dp[i - 1][2] + (cows[i] != 3);
        rev_dp[i][1] =
            std::min(rev_dp[i - 1][2], rev_dp[i - 1][1]) + (cows[i] != 2);
        rev_dp[i][0] =
            std::min({rev_dp[i - 1][0], rev_dp[i - 1][1], rev_dp[i - 1][2]}) +
            (cows[i] != 1);
    }

    std::cout << std::min({dp[N - 1][0], dp[N - 1][1], dp[N - 1][2],
                           rev_dp[N - 1][0], rev_dp[N - 1][1],
                           rev_dp[N - 1][2]})
              << '\n';

    return 0;
}
