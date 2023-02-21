#include <algorithm>
#include <iostream>
#include <limits>
#include <numeric>
#include <queue>
#include <vector>

int bfs(int N, const std::vector<std::vector<int>>& board) {
    using std::vector;

    // [x][y][k][t] = min distance to (x, y) after k numbers with type t
    vector<vector<vector<vector<int>>>> dist(
        N, vector<vector<vector<int>>>(
               N, vector<vector<int>>(
                      N * N, vector<int>(3, std::numeric_limits<int>::max()))));
    std::queue<std::tuple<int, int, int, int>> q;

    int sx, sy, tx, ty;
    for (int i = 0; i < N; ++i)
        for (int j = 0; j < N; ++j)
            if (board[i][j] == 1) {
                sx = i;
                sy = j;
            } else if (board[i][j] == N * N) {
                tx = i;
                ty = j;
            }

    for (int i = 0; i < 3; ++i) {
        dist[sx][sy][0][i] = 0;
        q.push({sx, sy, 0, i});
    }

    while (!q.empty()) {
        auto [x, y, k, t] = q.front();
        q.pop();

        for (int i = 0; i < 3; ++i)
            if (i != t && dist[x][y][k][i] > dist[x][y][k][t] + 1) {
                dist[x][y][k][i] = dist[x][y][k][t] + 1;
                q.push({x, y, k, i});
            }

        if (board[x][y] == k + 1) {
            if (board[x][y] == N * N) return dist[x][y][k][t];
            dist[x][y][k + 1][t] = dist[x][y][k][t];
            q.push({x, y, k + 1, t});
        }

        switch (t) {
            case 0: {
                int dx[] = {-2, -1, -2, -1, 2, 1, 2, 1};
                int dy[] = {-1, -2, 1, 2, -1, -2, 1, 2};

                for (int i = 0; i < 8; ++i) {
                    int nx = x + dx[i];
                    int ny = y + dy[i];

                    if (0 <= nx && nx < N && 0 <= ny && ny < N &&
                        dist[nx][ny][k][t] > dist[x][y][k][t] + 1) {
                        dist[nx][ny][k][t] = dist[x][y][k][t] + 1;
                        q.push({nx, ny, k, t});
                    }
                }
                break;
            }

            case 1: {
                int dx[] = {-1, -1, 1, 1};
                int dy[] = {-1, 1, -1, 1};

                for (int i = 0; i < 4; ++i)
                    for (int j = 1; j < N; ++j) {
                        int nx = x + dx[i] * j;
                        int ny = y + dy[i] * j;

                        if (0 <= nx && nx < N && 0 <= ny && ny < N &&
                            dist[nx][ny][k][t] > dist[x][y][k][t] + 1) {
                            dist[nx][ny][k][t] = dist[x][y][k][t] + 1;
                            q.push({nx, ny, k, t});
                        }
                    }
                break;
            }

            case 2: {
                int dx[] = {-1, 0, 1, 0};
                int dy[] = {0, -1, 0, 1};

                for (int i = 0; i < 4; ++i)
                    for (int j = 1; j < N; ++j) {
                        int nx = x + dx[i] * j;
                        int ny = y + dy[i] * j;

                        if (0 <= nx && nx < N && 0 <= ny && ny < N &&
                            dist[nx][ny][k][t] > dist[x][y][k][t] + 1) {
                            dist[nx][ny][k][t] = dist[x][y][k][t] + 1;
                            q.push({nx, ny, k, t});
                        }
                    }
                break;
            }
        }
    }

    return std::min({dist[tx][ty][N * N][0], dist[tx][ty][N * N][1],
                     dist[tx][ty][N * N][2]});
}

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    int N;
    std::cin >> N;

    std::vector<std::vector<int>> board(N, std::vector<int>(N));
    for (auto& row : board)
        for (auto& cell : row) std::cin >> cell;

    std::cout << bfs(N, board) << '\n';

    return 0;
}
