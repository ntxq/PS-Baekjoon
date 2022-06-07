#include <algorithm>
#include <cmath>
#include <iostream>
#include <vector>

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    const int LEN = std::log2(500000) + 1;

    int M;
    std::cin >> M;

    std::vector<std::vector<int>> dp(LEN + 1, std::vector<int>(M + 1));
    for (int i = 1; i <= M; ++i) std::cin >> dp[0][i];

    for (int i = 0; i < LEN; ++i)
        for (int j = 1; j <= M; ++j) dp[i + 1][j] = dp[i][dp[i][j]];

    int Q;
    std::cin >> Q;

    while (Q--) {
        int N, X;
        std::cin >> N >> X;

        for (int i = 0; N; ++i) {
            if (N % 2)
                X = dp[i][X];
            
            N = N >> 1;
        }

        std::cout << X << '\n';
    }

    return 0;
}