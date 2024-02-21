#include <algorithm>
#include <iostream>
#include <limits>
#include <numeric>
#include <vector>

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    int N, M;
    while (std::cin >> N >> M && N && M) {
        std::vector<std::vector<int>> board(N, std::vector<int>(M));
        for (auto& row : board)
            for (auto& cell : row) std::cin >> cell;

        int maxSquare = 0;
        for (int i = 0; i < N; ++i)
            for (int j = 0; j < M; ++j)
                if (board[i][j]) {
                    if (i && j && board[i - 1][j] && board[i][j - 1] &&
                        board[i - 1][j - 1])
                        board[i][j] +=
                            std::min({board[i - 1][j], board[i][j - 1],
                                      board[i - 1][j - 1]});
                    maxSquare = std::max(maxSquare, board[i][j]);
                }

        std::cout << maxSquare << '\n';
    }

    return 0;
}
