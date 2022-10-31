#include <algorithm>
#include <iostream>
#include <numeric>
#include <vector>

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    int N, M, K;
    std::cin >> N >> M >> K;

    std::vector<std::vector<bool>> board(N, std::vector<bool>(M));
    for (int i = 0; i < N; ++i)
        for (int j = 0; j < M; ++j) {
            char c;
            std::cin >> c;
            board[i][j] = c == 'B';
        }

    std::vector<std::vector<int>> blackSum(N, std::vector<int>(M));
    blackSum[0][0] = !board[0][0];
    for (int i = 0; i < N; ++i)
        for (int j = 0; j < M; ++j)
            if (i > 0 && j > 0)
                blackSum[i][j] =
                    blackSum[i - 1][j] + blackSum[i][j - 1] -
                    blackSum[i - 1][j - 1] +
                    ((i + j) % 2 == 0 ? !board[i][j] : board[i][j]);
            else if (i > 0)
                blackSum[i][j] =
                    blackSum[i - 1][j] +
                    ((i + j) % 2 == 0 ? !board[i][j] : board[i][j]);
            else if (j > 0)
                blackSum[i][j] =
                    blackSum[i][j - 1] +
                    ((i + j) % 2 == 0 ? !board[i][j] : board[i][j]);

    int minCount = K * K;
    for (int i = 0; i < N - K + 1; ++i)
        for (int j = 0; j < M - K + 1; ++j) {
            // black first repaint count from (i, j) to (i + K - 1, j + K - 1)
            const int blackCount =
                blackSum[i + K - 1][j + K - 1] -
                (i > 0 ? blackSum[i - 1][j + K - 1] : 0) -
                (j > 0 ? blackSum[i + K - 1][j - 1] : 0) +
                (i > 0 && j > 0 ? blackSum[i - 1][j - 1] : 0);

            // white first repaint count from (i, j) to (i + K - 1, j + K - 1)
            const int whiteCount = K * K - blackCount;

            minCount = std::min({minCount, blackCount, whiteCount});
        }

    std::cout << minCount << '\n';

    return 0;
}