#include <deque>
#include <iostream>
#include <limits>
#include <vector>

std::vector<std::vector<int>> bfs(const std::vector<std::vector<char>>& board,
                                  int h, int w, int sx, int sy) {
    std::deque<std::pair<int, int>> q;
    std::vector<std::vector<int>> dist(
        h, std::vector<int>(w, std::numeric_limits<int>::max()));

    q.push_back({sx, sy});
    dist[sx][sy] = 0;

    int dx[] = {0, 0, 1, -1};
    int dy[] = {1, -1, 0, 0};

    while (!q.empty()) {
        auto [x, y] = q.front();
        q.pop_front();

        for (int i = 0; i < 4; ++i) {
            int nx = x + dx[i];
            int ny = y + dy[i];

            if (0 <= nx && nx < h && 0 <= ny && ny < w) {
                if (board[nx][ny] == '#' && dist[x][y] + 1 < dist[nx][ny]) {
                    dist[nx][ny] = dist[x][y] + 1;
                    q.push_back({nx, ny});
                } else if ((board[nx][ny] == '.' || board[nx][ny] == '$') &&
                           dist[x][y] < dist[nx][ny]) {
                    dist[nx][ny] = dist[x][y];
                    q.push_front({nx, ny});
                }
            }
        }
    }

    return dist;
}

int solve(const std::vector<std::vector<char>>& board, int h, int w, int xA,
          int yA, int xB, int yB) {
    auto fromOutside{bfs(board, h, w, 0, 0)};
    auto fromA{bfs(board, h, w, xA, yA)};
    auto fromB{bfs(board, h, w, xB, yB)};

    int minCost = std::numeric_limits<int>::max();
    for (int i = 0; i < h; ++i)
        for (int j = 0; j < w; ++j)
            if (board[i][j] != '*') {
                int cost = fromOutside[i][j] + fromA[i][j] + fromB[i][j];
                if (board[i][j] == '#') cost -= 2;

                if (cost < minCost) minCost = cost;
            }

    return minCost;
}

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    int T;
    std::cin >> T;

    while (T--) {
        int h, w;
        std::cin >> h >> w;

        h += 2;
        w += 2;

        int xA, yA, xB, yB;
        xA = yA = xB = yB = -1;

        std::vector<std::vector<char>> board(h, std::vector<char>(w, '.'));
        for (int i = 1; i < h - 1; ++i)
            for (int j = 1; j < w - 1; ++j) {
                std::cin >> board[i][j];

                if (board[i][j] == '$' && xA == -1) {
                    xA = i;
                    yA = j;
                } else if (board[i][j] == '$' && xB == -1) {
                    xB = i;
                    yB = j;
                }
            }

        std::cout << solve(board, h, w, xA, yA, xB, yB) << '\n';
    }

    return 0;
}
