#include <algorithm>
#include <iostream>
#include <queue>
#include <tuple>
#include <vector>

int bfs(std::queue<std::tuple<int, int, int>>& q,
        std::vector<std::vector<std::vector<int>>>& tomatoes, int m, int n,
        int h) {
    int count = 0;

    while (!q.empty()) {
        ++count;
        int curSize = q.size();

        for (int i = 0; i < curSize; ++i) {
            auto [z, y, x] = q.front();
            q.pop();

            int dx[] = {-1, 1, 0, 0, 0, 0};
            int dy[] = {0, 0, -1, 1, 0, 0};
            int dz[] = {0, 0, 0, 0, -1, 1};

            for (int j = 0; j < 6; ++j) {
                int nx = x + dx[j];
                int ny = y + dy[j];
                int nz = z + dz[j];

                if (0 <= nx && nx < m && 0 <= ny && ny < n && 0 <= nz &&
                    nz < h && tomatoes[nz][ny][nx] == 0) {
                    tomatoes[nz][ny][nx] = 1;
                    q.push({nz, ny, nx});
                }
            }
        }
    }

    if (std::any_of(tomatoes.cbegin(), tomatoes.cend(), [&](const auto& v) {
            return std::any_of(v.cbegin(), v.cend(), [&](const auto& v) {
                return std::any_of(v.cbegin(), v.cend(),
                                   [&](const auto& v) { return !v; });
            });
        }))
        return -1;

    return count - 1;
}

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    int m, n, h;
    std::cin >> m >> n >> h;

    std::vector<std::vector<std::vector<int>>> tomatoes;
    std::queue<std::tuple<int, int, int>> q;

    for (int i = 0; i < h; ++i) {
        tomatoes.emplace_back();
        for (int j = 0; j < n; ++j) {
            tomatoes.back().emplace_back();
            for (int k = 0; k < m; ++k) {
                int cell;
                std::cin >> cell;

                tomatoes.back().back().push_back(cell);
                if (cell == 1) q.push({i, j, k});
            }
        }
    }

    std::cout << bfs(q, tomatoes, m, n, h);

    return 0;
}