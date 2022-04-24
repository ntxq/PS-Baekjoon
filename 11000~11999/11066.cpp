#include <algorithm>
#include <iostream>
#include <limits>
#include <vector>

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    int T;
    std::cin >> T;

    for (int t = 0; t < T; ++t) {
        int K;
        std::cin >> K;

        std::vector<std::vector<int>> w(K, std::vector<int>(K));
        for (int i = 0; i < K; ++i) {
            int size;
            std::cin >> size;
            w[i][i] = size;
        }

        for (int i = 0; i < K; ++i)
            for (int j = i + 1; j < K; ++j) w[i][j] = w[i][j - 1] + w[j][j];

        std::vector<std::vector<int>> dp(K, std::vector<int>(K));
        for (int l = 1; l < K; ++l) {
            for (int i = 0; i < K - l; ++i) {
                int j = i + l;
                dp[i][j] = std::numeric_limits<int>::max();

                for (int k = i; k <= j; ++k) {
                    int left = (k >= i) ? dp[i][k] : 0;
                    int right = (k < j) ? dp[k + 1][j] : 0;
                    dp[i][j] = std::min(dp[i][j], left + right + w[i][j]);
                }
            }
        }

        std::cout << dp[0][K - 1] << '\n';
    }

    return 0;
}