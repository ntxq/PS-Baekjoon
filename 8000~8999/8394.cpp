#include <algorithm>
#include <iostream>
#include <limits>
#include <string>
#include <vector>

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    int N;
    std::cin >> N;

    std::vector<int> dp(N + 1);
    dp[0] = 1;
    dp[1] = 1;

    for (int i = 2; i <= N; ++i) {
        dp[i] = dp[i - 1] + dp[i - 2];
        dp[i] %= 10;
    }

    std::cout << dp[N] << '\n';

    return 0;
}
