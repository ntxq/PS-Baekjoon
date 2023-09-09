#include <algorithm>
#include <iostream>
#include <numeric>
#include <vector>

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    int N;
    std::cin >> N;

    std::vector<std::vector<int>> board(N, std::vector<int>(N));
    for (auto& row : board)
        for (auto& cell : row) std::cin >> cell;

    std::vector<std::vector<int>> dp(N, std::vector<int>(N));
    for (int i = 0; i < N; ++i)
        for (int j = 0; j < N; ++j)
            for (int k = 0; k <= i; ++k)
                for (int l = 0; l <= j; ++l)
                    if (board[i][j] > board[k][l])
                        dp[i][j] = std::max(dp[i][j], dp[k][l] + 1);

    std::cout << std::accumulate(
                     dp.begin(), dp.end(), 0,
                     [](int acc, const auto& row) {
                         return std::max(
                             acc, *std::max_element(row.begin(), row.end()));
                     }) +
                     1
              << '\n';

    return 0;
}
