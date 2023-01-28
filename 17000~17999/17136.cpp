#include <algorithm>
#include <iostream>
#include <limits>
#include <numeric>
#include <vector>

int maxSquareLength(int x, int y, bool board[10][10], bool isCovered[10][10]) {
    for (int length = 1; length < 5; ++length) {
        if (x + length == 10 || y + length == 10) return length;

        for (int i = 0; i < length; ++i)
            if (!board[x + i][y + length] || !board[x + length][y + i] ||
                isCovered[x + i][y + length] || isCovered[x + length][y + i])
                return length;

        if (!board[x + length][y + length] || isCovered[x + length][y + length])
            return length;
    }

    return 5;
}

void placePaper(int x, int y, int length, bool isCovered[10][10]) {
    for (int i = 0; i < length; ++i)
        isCovered[x + i][y + length - 1] = isCovered[x + length - 1][y + i] =
            true;
}

void undoPaper(int x, int y, int length, bool isCovered[10][10]) {
    for (int i = 0; i < length; ++i)
        for (int j = 0; j < length; ++j) isCovered[x + i][y + j] = false;
}

int backtrack(int idx, bool board[10][10], bool isCovered[10][10],
              int available[6]) {
    if (idx == 100) return 0;

    int x = idx / 10, y = idx % 10;
    if (!board[x][y] || isCovered[x][y])
        return backtrack(idx + 1, board, isCovered, available);

    int maxLength = maxSquareLength(x, y, board, isCovered);
    int minCost = 100;
    int placedLength = 0;

    for (int i = 1; i <= maxLength; ++i)
        if (available[i]) {
            placePaper(x, y, i, isCovered);
            --available[i];
            minCost = std::min(
                minCost, backtrack(idx + 1, board, isCovered, available) + 1);
            ++available[i];

            placedLength = i;
        }

    if (placedLength) undoPaper(x, y, placedLength, isCovered);
    return minCost;
}

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    bool board[10][10];
    for (int i = 0; i < 10; ++i)
        for (int j = 0; j < 10; ++j) std::cin >> board[i][j];

    bool isCovered[10][10]{};
    int available[6]{0, 5, 5, 5, 5, 5};

    int cost = backtrack(0, board, isCovered, available);
    std::cout << (cost > 25 ? -1 : cost) << '\n';

    return 0;
}
