#include <algorithm>
#include <iostream>
#include <limits>
#include <numeric>
#include <vector>

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    constexpr int MOD = 1000007;

    int N, M, C;
    std::cin >> N >> M >> C;

    std::vector<std::vector<int>> is_arcade(N + 1, std::vector<int>(M + 1, 0));
    for (int i = 1; i <= C; ++i) {
        int x, y;
        std::cin >> x >> y;
        is_arcade[x][y] = i;
    }

    // dp[i][j][k][l] = number of paths at (i, j)
    // with last arcade k and l visited arcades
    auto dp = std::vector<std::vector<std::vector<std::vector<int>>>>(
        N + 1, std::vector<std::vector<std::vector<int>>>(
                   M + 1, std::vector<std::vector<int>>(
                              C + 1, std::vector<int>(C + 1, 0))));

    if (is_arcade[1][1])
        dp[1][1][is_arcade[1][1]][1] = 1;
    else
        dp[1][1][0][0] = 1;

    for (int i = 1; i <= N; ++i)
        for (int j = 1; j <= M; ++j) {
            if (is_arcade[i][j]) {
                int cur_arcade = is_arcade[i][j];
                for (int k = 0; k < cur_arcade; ++k)
                    for (int l = 1; l <= C; ++l) {
                        dp[i][j][cur_arcade][l] += dp[i - 1][j][k][l - 1];
                        dp[i][j][cur_arcade][l] %= MOD;
                        dp[i][j][cur_arcade][l] += dp[i][j - 1][k][l - 1];
                        dp[i][j][cur_arcade][l] %= MOD;
                    }
            } else {
                for (int k = 0; k <= C; ++k)
                    for (int l = 0; l <= C; ++l) {
                        dp[i][j][k][l] += dp[i - 1][j][k][l];
                        dp[i][j][k][l] %= MOD;
                        dp[i][j][k][l] += dp[i][j - 1][k][l];
                        dp[i][j][k][l] %= MOD;
                    }
            }
        }

    std::vector<int> sums(C + 1, 0);
    for (int k = 0; k <= C; ++k)
        for (int l = 0; l <= C; ++l) {
            sums[l] += dp[N][M][k][l];
            sums[l] %= MOD;
        }

    for (int l = 0; l <= C; ++l) std::cout << sums[l] << ' ';

    return 0;
}
