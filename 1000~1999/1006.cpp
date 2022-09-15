#include <algorithm>
#include <iostream>
#include <limits>
#include <vector>

int N, W;
std::vector<std::vector<int>> enemies;
std::vector<std::vector<int>> dp;

void solve() {
    for (int i = 1; i < N; ++i) {
        int up = (enemies[i - 1][0] + enemies[i][0] <= W ? 1 : 2);
        int down = (enemies[i - 1][1] + enemies[i][1] <= W ? 1 : 2);
        int vertical = (enemies[i][0] + enemies[i][1] <= W ? 1 : 2);

        dp[i][0] = std::min(dp[i - 1][1] + up, dp[i - 1][2] + 1);
        dp[i][1] = std::min(dp[i - 1][0] + down, dp[i - 1][2] + 1);
        dp[i][2] = std::min({
            dp[i][0] + 1,
            dp[i][1] + 1,
            dp[i - 1][2] + vertical,
            (i == 1 ? 0 : dp[i - 2][2]) + up + down,
        });
    };
}

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    int T;
    std::cin >> T;

    while (T--) {
        std::cin >> N >> W;

        if (N == 1) {
            int e1, e2;
            std::cin >> e1 >> e2;

            std::cout << (e1 + e2 <= W ? 1 : 2) << '\n';
            continue;
        }

        enemies.assign(N, std::vector<int>(2));
        for (auto& i : enemies) std::cin >> i[0];
        for (auto& i : enemies) std::cin >> i[1];

        int ans = std::numeric_limits<int>::max();
        dp.assign(N, std::vector<int>(3, std::numeric_limits<int>::max()));

        // no connection
        dp[0][0] = dp[0][1] = 1;
        dp[0][2] = (enemies[0][0] + enemies[0][1] <= W ? 1 : 2);
        solve();
        ans = std::min(ans, dp[N - 1][2]);

        // top connection
        if (enemies[0][0] + enemies[N - 1][0] <= W) {
            int e = enemies[0][0];
            enemies[0][0] = W + 1;

            dp[0][0] = dp[0][1] = 1;
            dp[0][2] = 2;

            solve();
            ans = std::min(ans, dp[N - 1][1]);
            enemies[0][0] = e;
        }

        // bottom connection
        if (enemies[0][1] + enemies[N - 1][1] <= W) {
            int e = enemies[0][1];
            enemies[0][1] = W + 1;

            dp[0][0] = dp[0][1] = 1;
            dp[0][2] = 2;

            solve();
            ans = std::min(ans, dp[N - 1][0]);
            enemies[0][1] = e;
        }

        // both connection
        if (enemies[0][0] + enemies[N - 1][0] <= W &&
            enemies[0][1] + enemies[N - 1][1] <= W) {
            enemies[0][0] = enemies[0][1] = W + 1;

            dp[0][0] = dp[0][1] = 1;
            dp[0][2] = 2;

            solve();
            ans = std::min(ans, dp[N - 2][2]);
        }

        std::cout << ans << '\n';
    }

    return 0;
}