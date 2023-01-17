#include <algorithm>
#include <iostream>
#include <limits>
#include <numeric>
#include <queue>
#include <vector>

int R, C;

std::pair<std::pair<int, int>, std::pair<int, int>> findSwan(
    const std::vector<std::vector<char>>& board) {
    std::vector<std::pair<int, int>> swans;
    for (int i = 0; i < R; ++i)
        for (int j = 0; j < C; ++j)
            if (board[i][j] == 'L') swans.push_back({i, j});

    return {swans[0], swans[1]};
}

int bfs(const std::vector<std::vector<char>>& board) {
    std::queue<std::pair<int, int>> swanQ;
    std::queue<std::pair<int, int>> nextSwanQ;

    std::queue<std::pair<int, int>> waterQ;
    std::queue<std::pair<int, int>> nextWaterQ;

    std::vector<std::vector<bool>> visited(R, std::vector<bool>(C, false));
    std::vector<std::vector<bool>> isMelted(R, std::vector<bool>(C, false));

    auto [swan1, swan2] = findSwan(board);
    auto [sx1, sy1] = swan1;
    auto [sx2, sy2] = swan2;

    int dist = 0;
    swanQ.push(swan1);
    visited[sx1][sy1] = true;

    for (int i = 0; i < R; ++i)
        for (int j = 0; j < C; ++j)
            if (board[i][j] != 'X') {
                waterQ.push({i, j});
                isMelted[i][j] = true;
            }

    int dx[] = {0, 0, 1, -1};
    int dy[] = {1, -1, 0, 0};

    while (!visited[sx2][sy2]) {
        while (!visited[sx2][sy2] && !swanQ.empty()) {
            auto [x, y] = swanQ.front();
            swanQ.pop();

            for (int i = 0; i < 4; ++i) {
                int nx = x + dx[i];
                int ny = y + dy[i];

                if (0 <= nx && nx < R && 0 <= ny && ny < C &&
                    !visited[nx][ny]) {
                    if (!isMelted[nx][ny]) {
                        nextSwanQ.push({nx, ny});
                        visited[nx][ny] = true;
                    } else {
                        swanQ.push({nx, ny});
                        visited[nx][ny] = true;
                    }
                }
            }
        }

        while (!visited[sx2][sy2] && !waterQ.empty()) {
            auto [x, y] = waterQ.front();
            waterQ.pop();

            for (int i = 0; i < 4; ++i) {
                int nx = x + dx[i];
                int ny = y + dy[i];

                if (0 <= nx && nx < R && 0 <= ny && ny < C &&
                    !isMelted[nx][ny]) {
                    nextWaterQ.push({nx, ny});
                    isMelted[nx][ny] = true;
                }
            }
        }

        if (!visited[sx2][sy2]) {
            swanQ = nextSwanQ;
            waterQ = nextWaterQ;
            nextSwanQ = {};
            nextWaterQ = {};
            ++dist;
        }
    }

    return dist;
}

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    std::cin >> R >> C;

    std::vector<std::vector<char>> board(R, std::vector<char>(C));
    for (auto& row : board)
        for (auto& cell : row) std::cin >> cell;

    std::cout << bfs(board) << '\n';

    return 0;
}