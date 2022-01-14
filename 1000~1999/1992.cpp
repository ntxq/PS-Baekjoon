#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

std::string compressGrid(int x, int y, int size,
                         const std::vector<std::vector<char>>& grid) {
    if (std::all_of(grid.cbegin() + x, grid.cbegin() + x + size,
                    [&](const std::vector<char>& row) {
                        return std::all_of(
                            row.cbegin() + y, row.cbegin() + y + size,
                            [&](const char& c) { return c == grid[x][y]; });
                    }))
        return std::string(1, grid[x][y]);

    return '(' + compressGrid(x, y, size / 2, grid) +
           compressGrid(x, y + size / 2, size / 2, grid) +
           compressGrid(x + size / 2, y, size / 2, grid) +
           compressGrid(x + size / 2, y + size / 2, size / 2, grid) + ')';
}

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    int n;
    std::cin >> n;

    std::vector<std::vector<char>> grid(n, std::vector<char>(n));
    for (auto& row : grid)
        for (auto& c : row) std::cin >> c;

    std::cout << compressGrid(0, 0, n, grid);

    return 0;
}