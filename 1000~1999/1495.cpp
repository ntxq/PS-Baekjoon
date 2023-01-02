#include <algorithm>
#include <iostream>
#include <vector>

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    int N, S, M;
    std::cin >> N >> S >> M;

    std::vector<int> volume(N);
    for (auto& v : volume) std::cin >> v;

    std::vector<std::vector<bool>> dp(N + 1, std::vector<bool>(M + 1));

    dp[0][S] = true;
    for (int i = 0; i < N; ++i)
        for (int j = 0; j <= M; ++j)
            if (dp[i][j]) {
                if (int nVol = j + volume[i]; nVol <= M) dp[i + 1][nVol] = true;
                if (int nVol = j - volume[i]; nVol >= 0) dp[i + 1][nVol] = true;
            }

    int maxVol = -1;
    for (int i = 0; i <= M; ++i)
        if (dp[N][i]) maxVol = i;
    std::cout << maxVol << '\n';

    return 0;
}
