#include <algorithm>
#include <iostream>
#include <limits>
#include <map>
#include <numeric>
#include <string>
#include <vector>

void horizontal_flip(std::vector<int>& grid) {
    std::swap(grid[0], grid[2]);
    std::swap(grid[1], grid[3]);
}

void vertical_flip(std::vector<int>& grid) {
    std::swap(grid[0], grid[1]);
    std::swap(grid[2], grid[3]);
}

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    std::vector<int> grid{1, 2, 3, 4};

    char c;
    while (std::cin >> c && c) {
        switch (c) {
            case 'H':
                horizontal_flip(grid);
                break;
            case 'V':
                vertical_flip(grid);
                break;
            default:
                break;
        }
    }

    std::cout << grid[0] << ' ' << grid[1] << '\n'
              << grid[2] << ' ' << grid[3] << '\n';

    return 0;
}
