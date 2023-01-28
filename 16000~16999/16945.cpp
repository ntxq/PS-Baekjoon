#include <algorithm>
#include <iostream>
#include <limits>
#include <numeric>
#include <vector>

bool isMagicSquare(int square[3][3]) {
    int curSum = square[0][0] + square[0][1] + square[0][2];

    for (int i = 0; i < 3; ++i) {
        if (curSum != square[i][0] + square[i][1] + square[i][2]) return false;
        if (curSum != square[0][i] + square[1][i] + square[2][i]) return false;
    }

    if (curSum != square[0][0] + square[1][1] + square[2][2]) return false;
    if (curSum != square[0][2] + square[1][1] + square[2][0]) return false;

    return true;
}

int backtrack(int idx, int square[3][3], bool isUsed[10]) {
    if (idx == 9) return isMagicSquare(square) ? 0 : 1000;

    int x = idx / 3;
    int y = idx % 3;

    int original = square[x][y];
    int minCost = 1000;

    for (int i = 1; i <= 9; ++i)
        if (!isUsed[i]) {
            isUsed[i] = true;
            square[x][y] = i;
            minCost = std::min(minCost, std::abs(original - i) +
                                            backtrack(idx + 1, square, isUsed));
            square[x][y] = original;
            isUsed[i] = false;
        }

    return minCost;
}

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    int magic[3][3];
    for (int i = 0; i < 3; ++i)
        for (int j = 0; j < 3; ++j) std::cin >> magic[i][j];

    bool isUsed[10]{};

    std::cout << backtrack(0, magic, isUsed) << '\n';

    return 0;
}
