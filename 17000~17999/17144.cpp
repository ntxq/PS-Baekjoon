#include <iostream>
#include <numeric>
#include <vector>

std::vector<std::vector<int>> spreadDust(
    const std::vector<std::vector<int>>& grid, int r, int c) {
    auto newGrid(grid);

    for (int i = 0; i < r; ++i) {
        for (int j = 0; j < c; ++j) {
            if (grid[i][j]) {
                const int spread = grid[i][j] / 5;

                int dx[] = {-1, 1, 0, 0};
                int dy[] = {0, 0, -1, 1};

                for (int k = 0; k < 4; ++k) {
                    int nx = i + dx[k];
                    int ny = j + dy[k];

                    if (0 <= nx && nx < r && 0 <= ny && ny < c &&
                        grid[nx][ny] != -1) {
                        newGrid[nx][ny] += spread;
                        newGrid[i][j] -= spread;
                    }
                }
            }
        }
    }

    return newGrid;
}

void filterDust(std::vector<std::vector<int>>& grid, int airFilter, int r,
                int c) {
    if (airFilter > 1) grid[airFilter - 2][0] = 0;
    for (int i = airFilter - 2; i > 0; --i) {
        grid[i][0] = grid[i - 1][0];
        grid[i - 1][0] = 0;
    }

    if (airFilter < r - 1) grid[airFilter + 1][0] = 0;
    for (int i = airFilter + 1; i < r - 1; ++i) {
        grid[i][0] = grid[i + 1][0];
        grid[i + 1][0] = 0;
    }

    for (int i = 0; i < c - 1; ++i) {
        grid[0][i] = grid[0][i + 1];
        grid[0][i + 1] = 0;

        grid[r - 1][i] = grid[r - 1][i + 1];
        grid[r - 1][i + 1] = 0;
    }

    for (int i = 0; i < airFilter - 1; ++i) {
        grid[i][c - 1] = grid[i + 1][c - 1];
        grid[i + 1][c - 1] = 0;
    }

    for (int i = r - 1; i > airFilter; --i) {
        grid[i][c - 1] = grid[i - 1][c - 1];
        grid[i - 1][c - 1] = 0;
    }

    for (int i = c - 1; i > 1; --i) {
        grid[airFilter - 1][i] = grid[airFilter - 1][i - 1];
        grid[airFilter - 1][i - 1] = 0;

        grid[airFilter][i] = grid[airFilter][i - 1];
        grid[airFilter][i - 1] = 0;
    }
}

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    int r, c, t;
    std::cin >> r >> c >> t;

    int airFilter = -1;
    std::vector<std::vector<int>> grid(r, std::vector<int>(c));

    for (int i = 0; i < r; ++i) {
        for (int j = 0; j < c; ++j) {
            std::cin >> grid[i][j];

            if (grid[i][j] == -1) airFilter = i;
        }
    }

    for (int i = 0; i < t; ++i) {
        grid = spreadDust(grid, r, c);
        filterDust(grid, airFilter, r, c);
    }

    std::cout << std::accumulate(
        grid.begin(), grid.end(), 2, [](int acc, const std::vector<int>& row) {
            return acc + std::accumulate(row.begin(), row.end(), 0);
        });

    return 0;
}