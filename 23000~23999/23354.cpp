#include <algorithm>
#include <array>
#include <iostream>
#include <limits>
#include <numeric>
#include <queue>
#include <vector>

std::vector<std::vector<int>> dijkstra(
    int sx, int sy, const std::vector<std::vector<int>>& board, int N) {
    std::priority_queue<std::tuple<int, int, int>,
                        std::vector<std::tuple<int, int, int>>,
                        std::greater<std::tuple<int, int, int>>>
        pq;
    std::vector<std::vector<int>> dist(
        N, std::vector<int>(N, std::numeric_limits<int>::max()));

    pq.push({0, sx, sy});
    dist[sx][sy] = 0;

    int dx[]{0, 0, 1, -1};
    int dy[]{1, -1, 0, 0};
    while (!pq.empty()) {
        auto [d, x, y] = pq.top();
        pq.pop();

        if (d != dist[x][y]) continue;

        for (int i = 0; i < 4; ++i) {
            int nx = x + dx[i];
            int ny = y + dy[i];

            if (nx < 0 || nx >= N || ny < 0 || ny >= N) continue;

            int nd = d + board[nx][ny];
            if (board[nx][ny] == -1) nd = d;

            if (dist[nx][ny] > nd) {
                pq.push({nd, nx, ny});
                dist[nx][ny] = nd;
            }
        }
    }

    return dist;
}

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    int N;
    std::cin >> N;

    std::vector<std::vector<int>> board(N, std::vector<int>(N));

    int sx, sy;
    std::vector<std::pair<int, int>> targets;
    for (int i = 0; i < N; ++i)
        for (int j = 0; j < N; ++j) {
            std::cin >> board[i][j];
            if (board[i][j] == -1) {
                sx = i;
                sy = j;
            } else if (board[i][j] == 0) {
                targets.push_back({i, j});
            }
        }

    const auto& startDist = dijkstra(sx, sy, board, N);
    std::vector<std::vector<int>> targetsDist(targets.size(),
                                              std::vector<int>(targets.size()));
    for (int i = 0; i < targets.size(); ++i) {
        const auto& curDist =
            dijkstra(targets[i].first, targets[i].second, board, N);
        for (int j = 0; j < targets.size(); ++j)
            targetsDist[i][j] = curDist[targets[j].first][targets[j].second];
    }

    std::vector<int> order(targets.size());
    std::iota(order.begin(), order.end(), 0);

    int minDist = std::numeric_limits<int>::max();
    if (targets.empty())
        minDist = 0;
    else
        do {
            int curDist =
                startDist[targets[order[0]].first][targets[order[0]].second];
            for (int i = 1; i < order.size(); ++i)
                curDist += targetsDist[order[i - 1]][order[i]];
            curDist += startDist[targets[order.back()].first]
                                [targets[order.back()].second];
            minDist = std::min(minDist, curDist);
        } while (std::next_permutation(order.begin(), order.end()));

    std::cout << minDist << '\n';

    return 0;
}
