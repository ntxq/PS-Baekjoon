#include <algorithm>
#include <iostream>
#include <array>

unsigned long long binomialCoeff(int n, int k) {
    static std::array<std::array<unsigned long long, 1001>, 1001> dp{};

    if (k > n)
        return 0;

    if (k == 0 || k == n)
        return 1;

    if (dp[n][k])
        return dp[n][k];

    return dp[n][k] = (binomialCoeff(n - 1, k - 1) + binomialCoeff(n - 1, k)) % 10007;
}

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    int N, K;
    std::cin >> N >> K;

    std::cout << binomialCoeff(N, K) << '\n';

    return 0;
}
