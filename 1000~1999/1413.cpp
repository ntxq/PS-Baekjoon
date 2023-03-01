#include <algorithm>
#include <iostream>
#include <limits>
#include <numeric>
#include <vector>

/*
Subproblem:
    dp[i][j] = number of ways to open i boxes with j bombs
Recurrence:
    dp[i][j] =
        (i-1) * dp[i-1][j]  // new box is added to a cycle
        + dp[i-1][j-1]      // new box is a new cycle
*/

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    int N, M;
    std::cin >> N >> M;

    std::vector<std::vector<long long>> dp(N + 1,
                                           std::vector<long long>(N + 1));
    dp[0][0] = 1;
    for (int i = 1; i <= N; ++i)
        for (int j = 1; j <= N; ++j)
            dp[i][j] = (i - 1) * dp[i - 1][j] + dp[i - 1][j - 1];

    long long possible =
        std::accumulate(dp[N].begin(), dp[N].begin() + M + 1, 0LL);
    long long total = std::accumulate(dp[N].begin(), dp[N].end(), 0LL);
    long long factor = std::gcd(possible, total);

    std::cout << possible / factor << '/' << total / factor << '\n';

    return 0;
}
