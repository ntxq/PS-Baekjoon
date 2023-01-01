#include <algorithm>
#include <iostream>
#include <vector>

using Maze = std::vector<std::vector<int>>;

int solve(const Maze& maze, int rows, int cols) {
    Maze dp(rows, std::vector<int>(cols));

    for (int i = 0; i < rows; ++i)
        for (int j = 0; j < cols; ++j)
            dp[i][j] = maze[i][j] + std::max(i > 0 ? dp[i - 1][j] : 0,
                                             j > 0 ? dp[i][j - 1] : 0);

    return dp[rows - 1][cols - 1];
}

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    int N, M;
    std::cin >> N >> M;

    Maze maze(N, std::vector<int>(M));
    for (auto& row : maze)
        for (auto& cell : row) std::cin >> cell;

    std::cout << solve(maze, N, M) << '\n';

    return 0;
}
