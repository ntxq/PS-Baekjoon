#include <algorithm>
#include <iostream>
#include <queue>
#include <utility>
#include <vector>

typedef std::pair<int, int> Point;

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    int T;
    std::cin >> T;

    for (int t = 0; t < T; ++t) {
        int l;
        std::cin >> l;

        Point start, end;
        std::cin >> start.first >> start.second >> end.first >> end.second;

        std::vector<std::vector<int>> dist(l, std::vector<int>(l));
        std::queue<Point> q;

        dist[start.first][start.second] = 1;
        q.push(start);
        while (!q.empty() && !dist[end.first][end.second]) {
            auto [x, y] = q.front();
            q.pop();

            int dx[8] = {-2, -1, 1, 2, -2, -1, 1, 2};
            int dy[8] = {1, 2, 2, 1, -1, -2, -2, -1};
            for (int i = 0; i < 8; ++i) {
                int nx = x + dx[i];
                int ny = y + dy[i];

                if (0 <= nx && nx < l && 0 <= ny && ny < l && !dist[nx][ny]) {
                    dist[nx][ny] = dist[x][y] + 1;
                    q.push({nx, ny});
                }
            }
        }

        std::cout << dist[end.first][end.second] - 1 << '\n';
    }

    return 0;
}