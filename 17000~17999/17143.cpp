#include <algorithm>
#include <iostream>
#include <tuple>
#include <vector>

enum DIRECTION { NONE, UP, DOWN, RIGHT, LEFT };

int catchShark(int location, std::vector<std::vector<int>>& grid,
               const std::vector<std::tuple<int, int, int>>& sharks) {
    for (unsigned i = 0; i < grid.size(); ++i) {
        if (grid[i][location]) {
            int size = std::get<2>(sharks[grid[i][location]]);
            grid[i][location] = 0;
            return size;
        }
    }

    return 0;
}

std::vector<std::vector<int>> moveShakrs(
    const std::vector<std::vector<int>>& grid,
    std::vector<std::tuple<int, int, int>>& sharks, int R, int C) {
    std::vector<std::vector<int>> nextGrid(R, std::vector<int>(C));

    for (int i = 0; i < R; ++i) {
        for (int j = 0; j < C; ++j) {
            if (grid[i][j]) {
                auto [s, d, z] = sharks[grid[i][j]];

                int nextR;
                int nextC;

                switch (d) {
                    case UP:
                        nextR = i - s;
                        nextC = j;
                        break;
                    case DOWN:
                        nextR = i + s;
                        nextC = j;
                        break;
                    case LEFT:
                        nextR = i;
                        nextC = j - s;
                        break;
                    case RIGHT:
                        nextR = i;
                        nextC = j + s;
                        break;
                    default:
                        break;
                }

                while (nextR < 0 || nextR >= R) {
                    if (nextR < 0) {
                        nextR *= -1;
                        std::get<1>(sharks[grid[i][j]]) = DOWN;
                    } else if (nextR >= R) {
                        nextR = 2 * (R - 1) - nextR;
                        std::get<1>(sharks[grid[i][j]]) = UP;
                    }
                }

                while (nextC < 0 || nextC >= C) {
                    if (nextC < 0) {
                        nextC *= -1;
                        std::get<1>(sharks[grid[i][j]]) = RIGHT;
                    } else if (nextC >= C) {
                        nextC = 2 * (C - 1) - nextC;
                        std::get<1>(sharks[grid[i][j]]) = LEFT;
                    }
                }

                if (nextGrid[nextR][nextC]) {
                    int prevSize = std::get<2>(sharks[nextGrid[nextR][nextC]]);
                    if (prevSize < z) nextGrid[nextR][nextC] = grid[i][j];
                } else {
                    nextGrid[nextR][nextC] = grid[i][j];
                }
            }
        }
    }

    return nextGrid;
}

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    int R, C, M;
    std::cin >> R >> C >> M;

    std::vector<std::vector<int>> grid(R, std::vector<int>(C));
    std::vector<std::tuple<int, int, int>> sharks(M + 1);

    for (int i = 0; i < M; ++i) {
        int r, c, s, d, z;
        std::cin >> r >> c >> s >> d >> z;

        grid[r - 1][c - 1] = i + 1;
        sharks[i + 1] = {s, d, z};
    }

    int sizeSum = 0;
    for (int i = 0; i < C; ++i) {
        sizeSum += catchShark(i, grid, sharks);
        grid = moveShakrs(grid, sharks, R, C);
    }

    std::cout << sizeSum << '\n';

    return 0;
}
