#include <iostream>
#include <limits>
#include <queue>
#include <vector>

struct State {
    int x, y, dir, cost;
};

int bfs(int sx, int sy, int tx, int ty,
        const std::vector<std::vector<bool>>& board, int w, int h) {
    std::queue<State> q;
    std::vector<std::vector<std::vector<int>>> visited(
        h, std::vector<std::vector<int>>(
               w, std::vector<int>(4, std::numeric_limits<int>::max())));
    int dist = std::numeric_limits<int>::max();

    int dx[] = {1, 0, -1, 0};
    int dy[] = {0, 1, 0, -1};

    for (int i = 0; i < 4; ++i) {
        int nx = sx + dx[i];
        int ny = sy + dy[i];

        if (0 <= nx && nx < h && 0 <= ny && ny < w && !board[nx][ny]) {
            q.push({nx, ny, i, 0});
            visited[nx][ny][i] = 0;
        }
    }

    while (!q.empty()) {
        auto [x, y, dir, cost] = q.front();
        q.pop();

        if (x == tx && y == ty && cost < dist) dist = cost;
        if (cost > dist) continue;

        int nx = x + dx[dir];
        int ny = y + dy[dir];
        if (0 <= nx && nx < h && 0 <= ny && ny < w && !board[nx][ny] &&
            cost < visited[nx][ny][dir]) {
            q.push({nx, ny, dir, cost});
            visited[nx][ny][dir] = cost;
        }

        for (int i = 0; i < 4; ++i) {
            int nx = x + dx[i];
            int ny = y + dy[i];
            int nCost = cost + 1;

            if (i != dir && 0 <= nx && nx < h && 0 <= ny && ny < w &&
                !board[nx][ny] && nCost < visited[nx][ny][i]) {
                q.push({nx, ny, i, nCost});
                visited[nx][ny][i] = nCost;
            }
        }
    }

    return dist;
}

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    int w, h;
    std::cin >> w >> h;

    std::vector<std::vector<bool>> board(h, std::vector<bool>(w));
    int sx, sy, tx, ty;
    sx = sy = tx = ty = -1;
    for (int i = 0; i < h; ++i)
        for (int j = 0; j < w; ++j) {
            char c;
            std::cin >> c;
            board[i][j] = c == '*';

            if (c == 'C') {
                if (sx == -1) {
                    sx = i;
                    sy = j;
                } else {
                    tx = i;
                    ty = j;
                }
            }
        }

    std::cout << bfs(sx, sy, tx, ty, board, w, h) << '\n';

    return 0;
}
