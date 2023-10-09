#include <algorithm>
#include <iostream>
#include <limits>
#include <numeric>
#include <vector>

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    int N, M, K;
    std::cin >> N >> M >> K;

    std::vector<int> A(N);
    for (int& a : A) std::cin >> a;

    std::vector<std::vector<int>> dp(M + 1, std::vector<int>(K, -1));
    dp[0][0] = 0;

    for (int i = 1; i <= M; ++i)
        for (int j = 0; j < K; ++j)
            for (int k = 0; k < N; ++k) {
                int before = (j - (A[k] % K) + K) % K;
                if (dp[i - 1][before] == -1) continue;

                dp[i][j] = std::max(dp[i][j], dp[i - 1][before] + A[k]);
            }
    int max_candy = 0;
    for (int i = 0; i <= M; ++i) max_candy = std::max(max_candy, dp[i][0]);

    std::cout << max_candy << '\n';

    return 0;
}
