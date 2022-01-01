#include <algorithm>
#include <iostream>
#include <utility>
#include <vector>

std::pair<int, int> operator+(const std::pair<int, int>& lhs,
                              const std::pair<int, int>& rhs) {
    return std::make_pair(lhs.first + rhs.first, lhs.second + rhs.second);
}

std::pair<int, int> countSplit(int size, int x, int y,
                               const std::vector<std::vector<bool>>& matrix) {
    bool uniform = true;

    bool color = matrix[x][y];
    for (int i = x; i < x + size && uniform; ++i)
        for (int j = y; j < y + size && uniform; ++j)
            if (matrix[i][j] != color) uniform = false;

    if (uniform) return (color ? std::make_pair(0, 1) : std::make_pair(1, 0));

    return countSplit(size / 2, x, y, matrix) +
           countSplit(size / 2, x, y + size / 2, matrix) +
           countSplit(size / 2, x + size / 2, y, matrix) +
           countSplit(size / 2, x + size / 2, y + size / 2, matrix);
}

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    int size;
    std::cin >> size;

    std::vector<std::vector<bool>> matrix(size, std::vector<bool>(size, false));
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            bool color;
            std::cin >> color;
            matrix[i][j] = color;
        }
    }

    auto count = countSplit(size, 0, 0, matrix);
    std::cout << count.first << '\n' << count.second;

    return 0;
}