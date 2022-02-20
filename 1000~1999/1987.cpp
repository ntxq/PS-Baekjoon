#include <iostream>
#include <vector>

int backtrack(int x, int y, const std::vector<std::vector<char>>& grid, int r,
              int c) {
    static std::vector<bool> visited(26);

    visited[grid[x][y] - 'A'] = true;

    int dx[] = {0, 0, 1, -1};
    int dy[] = {1, -1, 0, 0};

    int max = 0;
    for (int i = 0; i < 4; ++i) {
        int nx = x + dx[i];
        int ny = y + dy[i];

        if (0 <= nx && nx < r && 0 <= ny && ny < c &&
            !visited[grid[nx][ny] - 'A'])
            if (int tmp = backtrack(nx, ny, grid, r, c); tmp > max) max = tmp;
    }

    visited[grid[x][y] - 'A'] = false;

    return max + 1;
}

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    int r, c;
    std::cin >> r >> c;

    std::vector<std::vector<char>> grid(r, std::vector<char>(c));
    for (auto& row : grid)
        for (auto& cell : row) std::cin >> cell;

    std::cout << backtrack(0, 0, grid, r, c) << '\n';

    return 0;
}
