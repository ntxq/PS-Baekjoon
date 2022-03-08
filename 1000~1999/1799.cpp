#include <algorithm>
#include <iostream>
#include <numeric>
#include <optional>
#include <string>
#include <vector>

unsigned backtrack(unsigned x, unsigned y, unsigned sum,
                   std::vector<bool>& leftDiagonal,
                   std::vector<bool>& rightDiagonal,
                   const std::vector<std::vector<bool>>& board) {
    if (y >= board.size()) {
        ++x;
        y = !(y % 2);
    }

    if (x >= board.size()) return sum;

    int maxSum = sum;
    if (board[x][y] && !leftDiagonal[board.size() + y - x - 1] &&
        !rightDiagonal[x + y]) {
        leftDiagonal[board.size() + y - x - 1] = rightDiagonal[x + y] = true;
        int curSum =
            backtrack(x, y + 2, sum + 1, leftDiagonal, rightDiagonal, board);
        leftDiagonal[board.size() + y - x - 1] = rightDiagonal[x + y] = false;

        if (curSum > maxSum) maxSum = curSum;
    }

    int curSum = backtrack(x, y + 2, sum, leftDiagonal, rightDiagonal, board);
    if (curSum > maxSum) maxSum = curSum;

    return maxSum;
}

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    int n;
    std::cin >> n;

    std::vector<std::vector<bool>> board(n, std::vector<bool>(n));
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            if (bool b; std::cin >> b) board[i][j] = b;

    std::vector<bool> leftDiagonal(2 * n - 1);
    std::vector<bool> rightDiagonal(2 * n - 1);

    int sum = backtrack(0, 0, 0, leftDiagonal, rightDiagonal, board);
    for (int i = 0; i < 2 * n - 1; ++i)
        leftDiagonal[i] = rightDiagonal[i] = false;
    sum += backtrack(0, 1, 0, leftDiagonal, rightDiagonal, board);

    std::cout << sum << '\n';

    return 0;
}
