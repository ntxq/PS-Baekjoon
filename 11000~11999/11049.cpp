#include <array>
#include <iostream>
#include <vector>

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    int n;
    std::cin >> n;

    std::vector<std::array<int, 2>> v(n);
    for (int i = 0; i < n; ++i) std::cin >> v[i][0] >> v[i][1];

    std::vector<std::vector<unsigned long long>> dp(
        n, std::vector<unsigned long long>(n));
    for (int l = 1; l < n; ++l)
        for (int i = 0; i < n - l; ++i)
            for (int j = i + l, k = i; k < j; ++k)
                if (unsigned long long cost =
                        dp[i][k] + dp[k + 1][j] + v[i][0] * v[k][1] * v[j][1];
                    cost < dp[i][j] || !dp[i][j])
                    dp[i][j] = cost;

    std::cout << dp[0][n - 1];

    return 0;
}