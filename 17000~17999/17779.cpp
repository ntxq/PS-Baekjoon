#include <algorithm>
#include <iostream>
#include <limits>
#include <numeric>
#include <vector>

int getSector(int r, int c, int x, int y, int d1, int d2) {
    int topX = x;
    int bottomX = x + d1 + d2;

    int leftY;
    int rightY;
    if (r <= x + d1)
        leftY = y - (r - x);
    else
        leftY = (y - d1) + (r - (x + d1));

    if (r <= x + d2)
        rightY = y + (r - x);
    else
        rightY = (y + d2) - (r - (x + d2));

    if (topX <= r && r <= bottomX && leftY <= c && c <= rightY) {
        return 5;
    } else if (r < x + d1 && c <= y) {
        return 1;
    } else if (r <= x + d2 && y < c) {
        return 2;
    } else if (x + d1 <= r && c < y - d1 + d2) {
        return 3;
    } else if (x + d2 < r && y - d1 + d2 <= c) {
        return 4;
    }

    return 0;
}

int gerrymandering(int N, int x, int y, int d1, int d2,
                   const std::vector<std::vector<int>>& population) {
    std::vector<int> sectors(5);
    for (int i = 0; i < N; ++i)
        for (int j = 0; j < N; ++j)
            sectors[getSector(i, j, x, y, d1, d2) - 1] += population[i][j];

    std::sort(sectors.begin(), sectors.end());
    return sectors.back() - sectors.front();
}

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    int N;
    std::cin >> N;

    std::vector<std::vector<int>> population(N, std::vector<int>(N));
    for (auto& row : population)
        for (auto& p : row) std::cin >> p;

    int minDiff = std::numeric_limits<int>::max();
    for (int i = 0; i < N; ++i)
        for (int j = 0; j < N; ++j)
            for (int d1 = 1; d1 <= j; ++d1)
                for (int d2 = 1; i + d1 + d2 < N && j + d2 < N; ++d2)
                    minDiff = std::min(
                        minDiff, gerrymandering(N, i, j, d1, d2, population));

    std::cout << minDiff << '\n';

    return 0;
}