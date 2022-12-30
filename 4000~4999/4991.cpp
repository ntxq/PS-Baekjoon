#include <iostream>
#include <limits>
#include <queue>
#include <vector>

using Board = std::vector<std::vector<char>>;
struct State {
    int x, y, prev;
};

int bfs(const Board& board, int sx, int sy, int targets, int h, int w) {
    std::queue<State> q;
    std::vector<std::vector<std::vector<bool>>> visited(
        1 << targets, std::vector<std::vector<bool>>(h, std::vector<bool>(w)));

    q.push({sx, sy, 0});
    visited[0][sx][sy] = true;

    int dist = 0;
    int curSize = 1;

    int dx[] = {0, 0, 1, -1};
    int dy[] = {1, -1, 0, 0};

    while (!q.empty()) {
        int nextSize = 0;
        while (curSize--) {
            auto [x, y, prev] = q.front();
            q.pop();

            if (prev == (1 << targets) - 1) return dist;

            for (int i = 0; i < 4; ++i)
                if (int nx = x + dx[i], ny = y + dy[i]; 0 <= nx && nx < h &&
                                                        0 <= ny && ny < w &&
                                                        board[nx][ny] != 'x') {
                    int nPrev = (board[nx][ny] == '.')
                                    ? prev
                                    : prev | (1 << (board[nx][ny] - '0'));
                    if (!visited[nPrev][nx][ny]) {
                        visited[nPrev][nx][ny] = true;
                        q.push({nx, ny, nPrev});
                        ++nextSize;
                    }
                }
        }

        ++dist;
        curSize = nextSize;
    }

    return -1;
}

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    int w, h;
    while (std::cin >> w >> h && w && h) {
        Board board(h, std::vector<char>(w));

        int targets = 0;
        int sx, sy;

        for (int i = 0; i < h; ++i)
            for (int j = 0; j < w; ++j) {
                char c;
                std::cin >> c;

                switch (c) {
                    case '.':
                        board[i][j] = '.';
                        break;
                    case '*':
                        board[i][j] = '0' + targets++;
                        break;
                    case 'x':
                        board[i][j] = 'x';
                        break;
                    case 'o':
                        board[i][j] = '.';
                        sx = i;
                        sy = j;
                        break;
                }
            }

        std::cout << bfs(board, sx, sy, targets, h, w) << '\n';
    }

    return 0;
}
