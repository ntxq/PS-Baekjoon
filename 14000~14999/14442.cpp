#include <iostream>
#include <limits>
#include <queue>
#include <vector>

struct State {
    int x;
    int y;
    int cost;
    int passed;
};

int bfs(int rows, int cols, int walls,
        const std::vector<std::vector<bool>>& board) {
    std::queue<State> q;
    std::vector<std::vector<int>> visited(
        rows, std::vector<int>(cols, std::numeric_limits<int>::max()));
    int minDist = -1;

    q.push({0, 0, 1, 0});
    visited[0][0] = 0;

    int dx[] = {0, 0, 1, -1};
    int dy[] = {1, -1, 0, 0};

    while (!q.empty()) {
        auto [x, y, cost, passed] = q.front();
        q.pop();

        if (x == rows - 1 && y == cols - 1) {
            minDist = cost;
            break;
        }

        for (int i = 0; i < 4; ++i) {
            int nx = x + dx[i];
            int ny = y + dy[i];

            if (0 <= nx && nx < rows && 0 <= ny && ny < cols) {
                int nPassed = passed + (board[nx][ny] ? 1 : 0);
                if (nPassed < visited[nx][ny] && nPassed <= walls) {
                    visited[nx][ny] = nPassed;
                    q.push({nx, ny, cost + 1, nPassed});
                }
            }
        }
    }

    return minDist;
}

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    int rows, cols, walls;
    std::cin >> rows >> cols >> walls;

    std::vector<std::vector<bool>> board(rows, std::vector<bool>(cols));
    for (int i = 0; i < rows; ++i)
        for (int j = 0; j < cols; ++j) {
            char c;
            std::cin >> c;
            board[i][j] = c == '1';
        }

    std::cout << bfs(rows, cols, walls, board) << '\n';

    return 0;
}
