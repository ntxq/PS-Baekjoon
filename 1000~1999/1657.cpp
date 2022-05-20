#include <algorithm>
#include <iostream>
#include <vector>

template <typename T>
using Matrix = std::vector<std::vector<T>>;

const int table[5][5]{
    10, 8, 7, 5, 1, 8, 6, 4, 3, 1, 7, 4, 3, 2, 1, 5, 3, 2, 2, 1, 1, 1, 1, 1, 0,
};

int solve(int idx, int status, int N, int M, const Matrix<int>& levels) {
    static Matrix<int> dp(N * M, std::vector<int>(1 << M, -1));

    if (idx >= N * M) return 0;
    if (dp[idx][status] != -1) return dp[idx][status];
    if (status & 1)
        return dp[idx][status] = solve(idx + 1, status >> 1, N, M, levels);

    int horizontal, vertical, skip;
    horizontal = vertical = skip = 0;

    if (idx % M < (M - 1) && !(status & 2))
        horizontal =
            table[levels[idx / M][idx % M]][levels[idx / M][idx % M + 1]] +
            solve(idx + 2, status >> 2, N, M, levels);
    if (idx / M < (N - 1))
        vertical =
            table[levels[idx / M][idx % M]][levels[idx / M + 1][idx % M]] +
            solve(idx + 1, (status >> 1) | (1 << (M - 1)), N, M, levels);
    skip = solve(idx + 1, status >> 1, N, M, levels);

    return dp[idx][status] = std::max({horizontal, vertical, skip});
}

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    int N, M;
    std::cin >> N >> M;

    Matrix<int> levels(N, std::vector<int>(M));
    for (auto& row : levels)
        for (auto& level : row) {
            char c;
            std::cin >> c;

            switch (c) {
                case 'A':
                    level = 0;
                    break;
                case 'B':
                    level = 1;
                    break;
                case 'C':
                    level = 2;
                    break;
                case 'D':
                    level = 3;
                    break;
                case 'F':
                    level = 4;
                    break;
            }
        }

    std::cout << solve(0, 0, N, M, levels) << '\n';

    return 0;
}