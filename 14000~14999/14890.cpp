#include <algorithm>
#include <iostream>
#include <vector>

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    int N, L;
    std::cin >> N >> L;

    std::vector<std::vector<int>> board(N, std::vector<int>(N));
    for (auto& row : board)
        for (auto& i : row) std::cin >> i;

    std::vector<bool> isColSafe(N, true);
    std::vector<bool> isRowSafe(N, true);

    std::vector<std::vector<bool>> isColBridge(N, std::vector<bool>(N));
    std::vector<std::vector<bool>> isRowBridge(N, std::vector<bool>(N));

    for (int i = 0; i < N; ++i) {
        // Check col safety
        int prevHeight = board[0][i];
        int prevCount = 1;

        for (int j = 1; j < N && isColSafe[i]; ++j) {
            int curHeight = board[j][i];

            if (curHeight == prevHeight) {
                ++prevCount;
            } else if (curHeight == prevHeight + 1 && prevCount >= L) {
                bool canBuild = true;
                for (int k = j - L; k < j; ++k)
                    if (!isColBridge[k][i])
                        isColBridge[k][i] = true;
                    else
                        canBuild = false;

                if (!canBuild) isColSafe[i] = false;
                prevHeight = curHeight;
                prevCount = 1;
            } else if (curHeight == prevHeight - 1) {
                prevHeight = curHeight;
                prevCount = 1;
            } else {
                isColSafe[i] = false;
            }
        }

        prevHeight = board[N - 1][i];
        prevCount = 1;

        for (int j = N - 2; j >= 0 && isColSafe[i]; --j) {
            int curHeight = board[j][i];

            if (curHeight == prevHeight) {
                ++prevCount;
            } else if (curHeight == prevHeight + 1 && prevCount >= L) {
                bool canBuild = true;
                for (int k = j + 1; k <= j + L; ++k)
                    if (!isColBridge[k][i])
                        isColBridge[k][i] = true;
                    else
                        canBuild = false;

                if (!canBuild) isColSafe[i] = false;
                prevHeight = curHeight;
                prevCount = 1;
            } else if (curHeight == prevHeight - 1) {
                prevHeight = curHeight;
                prevCount = 1;
            } else {
                isColSafe[i] = false;
            }
        }

        // Check row safety
        prevHeight = board[i][0];
        prevCount = 1;

        for (int j = 1; j < N && isRowSafe[i]; ++j) {
            int curHeight = board[i][j];

            if (curHeight == prevHeight) {
                ++prevCount;
            } else if (curHeight == prevHeight + 1 && prevCount >= L) {
                bool canBuild = true;
                for (int k = j - L; k < j; ++k)
                    if (!isRowBridge[i][k])
                        isRowBridge[i][k] = true;
                    else
                        canBuild = false;

                if (!canBuild) isRowSafe[i] = false;
                prevHeight = curHeight;
                prevCount = 1;
            } else if (curHeight == prevHeight - 1) {
                prevHeight = curHeight;
                prevCount = 1;
            } else {
                isRowSafe[i] = false;
            }
        }

        prevHeight = board[i][N - 1];
        prevCount = 1;

        for (int j = N - 2; j >= 0 && isRowSafe[i]; --j) {
            int curHeight = board[i][j];

            if (curHeight == prevHeight) {
                ++prevCount;
            } else if (curHeight == prevHeight + 1 && prevCount >= L) {
                bool canBuild = true;
                for (int k = j + 1; k <= j + L; ++k)
                    if (!isRowBridge[i][k])
                        isRowBridge[i][k] = true;
                    else
                        canBuild = false;

                if (!canBuild) isRowSafe[i] = false;
                prevHeight = curHeight;
                prevCount = 1;
            } else if (curHeight == prevHeight - 1) {
                prevHeight = curHeight;
                prevCount = 1;
            } else {
                isRowSafe[i] = false;
            }
        }
    }

    std::cout << std::count(isColSafe.begin(), isColSafe.end(), true) +
                     std::count(isRowSafe.begin(), isRowSafe.end(), true)
              << '\n';

    return 0;
}