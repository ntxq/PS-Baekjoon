#include <algorithm>
#include <iostream>
#include <limits>
#include <vector>

using Maze = std::vector<int>;

int solve(const Maze& maze, int size) {
    Maze dp(size, std::numeric_limits<int>::max());

    dp[0] = 0;
    for (int i = 0; i < size; ++i)
        for (int j = 1; j <= maze[i] && i + j < size; ++j)
            if (dp[i] != std::numeric_limits<int>::max())
                dp[i + j] = std::min(dp[i + j], dp[i] + 1);

    return dp[size - 1] == std::numeric_limits<int>::max() ? -1 : dp[size - 1];
}

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    int N;
    std::cin >> N;

    Maze maze(N);
    for (auto& i : maze) std::cin >> i;

    std::cout << solve(maze, N) << '\n';

    return 0;
}
