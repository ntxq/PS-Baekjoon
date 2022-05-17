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

    for (int i = 1; i < N; ++i) {
        for (int j = 0; j < 10; ++j) {
            dist[i][j] = dist[i - 1][j] + dp[i][j];
            for (int k = 1; k < 10; ++k) {
                dist[i][j] = std::min(
                    dist[i][j], dist[i - 1][(j - k + 10) % 10] + dp[i][j] + k);
            }
        }
    }

    std::cout << *std::min_element(dist[N - 1].begin(), dist[N - 1].end())
              << '\n';

    return 0;
}