#include <iostream>
#include <limits>
#include <queue>
#include <vector>

using Board = std::vector<std::vector<bool>>;
struct State {
    int x, y, charge;
};

int bfs(const Board& board, int w, int h, int k) {
    std::queue<State> q;
    std::vector<std::vector<int>> visited(h, std::vector<int>(w, -1));

    q.push({0, 0, k});
    visited[0][0] = k;

    int dx[] = {1, -1, 0, 0};
    int dy[] = {0, 0, 1, -1};

    int hx[] = {2, 2, -2, -2, 1, 1, -1, -1};
    int hy[] = {1, -1, 1, -1, 2, -2, 2, -2};

    int curDist = 0;
    int curSize = 1;

    while (!q.empty()) {
        int nextSize = 0;
        while (curSize--) {
            auto [x, y, charge] = q.front();
            q.pop();

            if (x == h - 1 && y == w - 1) return curDist;

            for (int i = 0; i < 4; ++i) {
                int nx = x + dx[i];
                int ny = y + dy[i];

                if (0 <= nx && nx < h && 0 <= ny && ny < w && !board[nx][ny] &&
                    visited[nx][ny] < charge) {
                    q.push({nx, ny, charge});
                    visited[nx][ny] = charge;
                    ++nextSize;
                }
            }

            for (int i = 0; i < 8 && charge > 0; ++i) {
                int nx = x + hx[i];
                int ny = y + hy[i];

                if (0 <= nx && nx < h && 0 <= ny && ny < w && !board[nx][ny] &&
                    visited[nx][ny] < charge - 1) {
                    q.push({nx, ny, charge - 1});
                    visited[nx][ny] = charge - 1;
                    ++nextSize;
                }
            }
        }

        curSize = nextSize;
        ++curDist;
    }

    return -1;
}

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    int K;
    std::cin >> K;

    int W, H;
    std::cin >> W >> H;

    Board board(H, std::vector<bool>(W));
    for (int i = 0; i < H; ++i) {
        for (int j = 0; j < W; ++j) {
            bool isWall;
            std::cin >> isWall;
            board[i][j] = isWall;
        }
    }

    std::cout << bfs(board, W, H, K) << '\n';

    return 0;
}
