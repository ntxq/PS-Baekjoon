#include <algorithm>
#include <iostream>
#include <vector>

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    int N, K;
    std::cin >> N >> K;

    std::vector<int> C(N);
    for (int& coin : C) std::cin >> coin;

    std::vector<int> dp(K + 1);
    dp[0] = 1;

    for (int i = 0; i < N; ++i)
        for (int j = 0; j <= K; ++j)
            if (C[i] <= j) dp[j] = dp[j] + dp[j - C[i]];

    std::cout << dp[K] << '\n';

    return 0;
}