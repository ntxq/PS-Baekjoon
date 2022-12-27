#include <iostream>
#include <limits>
#include <queue>
#include <vector>

void move(std::vector<std::vector<bool>>& board) {
    for (int i = 6; i >= 0; --i)
        for (int j = 0; j < 8; ++j) board[i + 1][j] = board[i][j];

    for (int j = 0; j < 8; ++j) board[0][j] = false;
}

bool bfs(std::vector<std::vector<bool>>& board) {
    std::queue<std::pair<int, int>> q;
    std::vector<std::vector<int>> visited(8, std::vector<int>(8, 0));

    int toMove = 0;
    int dx[] = {1, 1, 1, 0, 0, -1, -1, -1, 0};
    int dy[] = {1, 0, -1, 1, -1, 1, 0, -1, 0};

    q.push({7, 0});
    visited[7][0] = 1;
    ++toMove;

    while (!q.empty() && visited[0][7] == 0) {
        int nextMoves = 0;

        while (toMove--) {
            auto [x, y] = q.front();
            int curDist = visited[x][y];
            q.pop();

            if (board[x][y]) continue;

            for (int i = 0; i < 9; ++i) {
                int nx = x + dx[i];
                int ny = y + dy[i];

                if (0 <= nx && nx < 8 && 0 <= ny && ny < 8 &&
                    visited[nx][ny] < curDist + 1 && !board[nx][ny]) {
                    q.push({nx, ny});
                    visited[nx][ny] = curDist + 1;
                    ++nextMoves;
                }
            }
        }

        toMove = nextMoves;
        move(board);
    }

    return visited[0][7] != 0;
}

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    std::vector<std::vector<bool>> board(8, std::vector<bool>(8));
    for (int i = 0; i < 8; ++i)
        for (int j = 0; j < 8; ++j) {
            char c;
            std::cin >> c;
            board[i][j] = c == '#';
        }

    std::cout << bfs(board) << '\n';

    return 0;
}
