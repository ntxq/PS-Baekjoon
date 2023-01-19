#include <algorithm>
#include <iostream>
#include <limits>
#include <numeric>
#include <vector>

int getValue(const std::vector<std::vector<int>>& matrix) {
    int minSum = std::numeric_limits<int>::max();
    for (auto& row : matrix)
        minSum = std::min(minSum, std::accumulate(row.begin(), row.end(), 0));

    return minSum;
}

void rotation(int r, int c, int s, std::vector<std::vector<int>>& matrix) {
    if (s == 0) return;

    int temp = matrix[r - s][c - s];

    for (int i = r - s; i < r + s; ++i) matrix[i][c - s] = matrix[i + 1][c - s];
    for (int i = c - s; i < c + s; ++i) matrix[r + s][i] = matrix[r + s][i + 1];
    for (int i = r + s; i > r - s; --i) matrix[i][c + s] = matrix[i - 1][c + s];
    for (int i = c + s; i > c - s + 1; --i)
        matrix[r - s][i] = matrix[r - s][i - 1];

    matrix[r - s][c - s + 1] = temp;

    rotation(r, c, s - 1, matrix);
}

int tryRotation(std::vector<std::vector<int>> matrix,
                const std::vector<std::tuple<int, int, int>>& rotations) {
    for (auto& [r, c, s] : rotations) rotation(r, c, s, matrix);

    return getValue(matrix);
}

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    int N, M, K;
    std::cin >> N >> M >> K;

    std::vector<std::vector<int>> matrix(N, std::vector<int>(M));
    for (auto& row : matrix)
        for (auto& cell : row) std::cin >> cell;

    std::vector<std::tuple<int, int, int>> rotations(K);
    for (int i = 0; i < K; ++i) {
        int r, c, s;
        std::cin >> r >> c >> s;
        rotations[i] = {r - 1, c - 1, s};
    }

    std::sort(rotations.begin(), rotations.end());

    int minSum = std::numeric_limits<int>::max();
    do {
        minSum = std::min(minSum, tryRotation(matrix, rotations));
    } while (std::next_permutation(rotations.begin(), rotations.end()));

    std::cout << minSum << '\n';

    return 0;
}