#include <algorithm>
#include <iostream>
#include <limits>
#include <queue>
#include <tuple>
#include <vector>

typedef std::tuple<int, int, int, int> Node;

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    int M, N;
    std::cin >> M >> N;

    std::vector<std::vector<int>> heights(M, std::vector<int>(N));
    for (auto& row : heights)
        for (auto& col : row) std::cin >> col;

    std::priority_queue<Node> pq;
    std::vector<std::vector<int>> count(M, std::vector<int>(N));

    count[0][0] = 1;
    pq.emplace(heights[0][0], 0, 0, 1);

    while (!pq.empty()) {
        auto [h, x, y, cnt] = pq.top();
        pq.pop();

        if (cnt != count[x][y]) continue;

        int dx[4] = {0, 0, 1, -1};
        int dy[4] = {1, -1, 0, 0};

        for (int i = 0; i < 4; ++i) {
            int nx = x + dx[i];
            int ny = y + dy[i];

            if (0 <= nx && nx < M && 0 <= ny && ny < N)
                if (heights[nx][ny] < h) {
                    count[nx][ny] += count[x][y];
                    pq.emplace(heights[nx][ny], nx, ny, count[nx][ny]);
                }
        }
    }

    std::cout << count[M - 1][N - 1] << '\n';

    return 0;
}