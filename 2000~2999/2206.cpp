#include <algorithm>
#include <iostream>
#include <queue>
#include <tuple>
#include <vector>

bool isValid(int x, int y, int n, int m) {
    return 0 <= x && x < n && 0 <= y && y < m;
}

int bfs(const std::vector<std::vector<bool>>& graph) {
    std::vector<std::vector<int>> dist(graph.size(),
                                       std::vector<int>(graph[0].size()));
    std::vector<std::vector<int>> wallDist(graph.size(),
                                           std::vector<int>(graph[0].size()));
    std::queue<std::tuple<int, int, bool>> q;

    dist[0][0] = 1;
    wallDist[0][0] = 1;
    q.push({0, 0, false});
    q.push({0, 0, true});

    while (!q.empty()) {
        auto [x, y, passWall] = q.front();
        q.pop();

        int dx[4] = {1, -1, 0, 0};
        int dy[4] = {0, 0, 1, -1};

        for (int i = 0; i < 4; ++i) {
            int nx = x + dx[i];
            int ny = y + dy[i];

            if (isValid(nx, ny, graph.size(), graph[0].size())) {
                if (!passWall) {
                    if (!graph[nx][ny] &&
                        (dist[x][y] + 1 < dist[nx][ny] || !dist[nx][ny])) {
                        dist[nx][ny] = dist[x][y] + 1;
                        q.push({nx, ny, false});
                    } else if (graph[nx][ny] &&
                               (dist[x][y] + 1 < wallDist[nx][ny] ||
                                !wallDist[nx][ny])) {
                        wallDist[nx][ny] = dist[x][y] + 1;
                        q.push({nx, ny, true});
                    }
                } else if (!graph[nx][ny] &&
                           (wallDist[x][y] + 1 < wallDist[nx][ny] ||
                            !wallDist[nx][ny])) {
                    wallDist[nx][ny] = wallDist[x][y] + 1;
                    q.push({nx, ny, true});
                }
            }
        }
    }

    if (int minDist = dist.back().back(), minWallDist = wallDist.back().back();
        !minDist && !minWallDist)
        return -1;
    else if (!minDist)
        return minWallDist;
    else if (!minWallDist)
        return minDist;
    else
        return std::min(minDist, minWallDist);
}

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    int n, m;
    std::cin >> n >> m;

    std::vector<std::vector<bool>> graph(n, std::vector<bool>(m));

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            char box;
            std::cin >> box;

            graph[i][j] = box == '1';
        }
    }

    std::cout << bfs(graph);

    return 0;
}