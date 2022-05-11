#include <algorithm>
#include <iostream>
#include <vector>

unsigned colorWheel(int n, int k) {
    if (k == 0) return 1;
    if (n == 1) return k == 1;

    std::vector<std::vector<unsigned>> dp(n, std::vector<unsigned>(k + 1));

    for (int i = 0; i < n; ++i) dp[i][0] = 1;
    dp[0][1] = 1;
    dp[1][1] = 2;

    for (int i = 2; i < n; ++i)
        for (int j = 1; j <= k; ++j)
            dp[i][j] = (dp[i - 1][j] + dp[i - 2][j - 1]) % 1000000003;

    return dp[n - 1][k];
}

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    int N, K;
    std::cin >> N >> K;

    unsigned count =
        (colorWheel(N - 1, K) + colorWheel(N - 3, K - 1)) % 1000000003;

    std::cout << count << '\n';

    return 0;
}