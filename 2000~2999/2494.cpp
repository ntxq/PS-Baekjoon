#include <algorithm>
#include <iostream>
#include <vector>

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    int N;
    std::cin >> N;

    std::vector<int> S(N);
    for (int i = 0; i < N; ++i) {
        char c;
        std::cin >> c;
        S[i] = c - '0';
    }

    std::vector<int> T(N);
    for (int i = 0; i < N; ++i) {
        char c;
        std::cin >> c;
        T[i] = c - '0';
    }

    std::vector<std::vector<int>> dp(N, std::vector<int>(10));
    for (int i = 0; i < N; ++i)
        for (int j = 0; j < 10; ++j) dp[i][j] = (S[i] + j - T[i] + 10) % 10;

    std::vector<std::vector<int>> dist(N, std::vector<int>(10));
    for (int i = 0; i < 10; ++i) dist[0][i] = dp[0][i] + i;

    std::vector<std::vector<int>> move(N, std::vector<int>(10));
    for (int i = 0; i < 10; ++i) move[0][i] = i - dp[0][i];

    for (int i = 1; i < N; ++i) {
        for (int j = 0; j < 10; ++j) {
            dist[i][j] = dist[i - 1][j] + dp[i][j];
            move[i][j] = -dp[i][j];

            for (int k = 1; k < 10; ++k) {
                int alt = dist[i - 1][(j - k + 10) % 10] + dp[i][j] + k;
                if (alt < dist[i][j]) {
                    dist[i][j] = alt;
                    move[i][j] = k - dp[i][j];
                }
            }
        }
    }

    auto minDist = std::min_element(dist.back().begin(), dist.back().end());
    std::cout << *minDist << '\n';

    std::vector<int> path;
    int curIdx = minDist - dist.back().begin();
    for (int i = N - 1; i >= 0; --i) {
        path.push_back(move[i][curIdx]);
        if (path.back() > 0) curIdx = (curIdx - path.back() + 10) % 10;
    }

    for (unsigned i = path.size() - 1; i < path.size(); --i)
        std::cout << N - i << ' ' << path[i] << '\n';

    return 0;
}