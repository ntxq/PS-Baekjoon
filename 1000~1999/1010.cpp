#include <algorithm>
#include <iostream>
#include <array>

unsigned long long binomialCoeff(int n, int k) {
    static std::array<std::array<unsigned long long, 51>, 51> dp{};

    if (k > n)
        return 0;

    if (k == 0 || k == n)
        return 1;

    if (dp[n][k])
        return dp[n][k];

    return dp[n][k] = (binomialCoeff(n - 1, k - 1) + binomialCoeff(n - 1, k));
}

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    int T;
    std::cin >> T;

    for (int i = 0; i < T; ++i) {
        int n, m;
        std::cin >> n >> m;

        std::cout << binomialCoeff(m, m - n) << '\n';
    }

    return 0;
}
