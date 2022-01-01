#include <iostream>
#include <queue>
#include <vector>

int bfs(std::vector<std::vector<int>>& tomatoes,
        std::queue<std::pair<unsigned, unsigned>>& q) {
    int days = 1;
    while (!q.empty()) {
        auto [x, y] = q.front();
        q.pop();

        if (tomatoes[x][y] > days) days = tomatoes[x][y];

        if (x > 0 && !tomatoes[x - 1][y]) {
            tomatoes[x - 1][y] = tomatoes[x][y] + 1;
            q.push({x - 1, y});
        }

        if (x < tomatoes.size() - 1 && !tomatoes[x + 1][y]) {
            tomatoes[x + 1][y] = tomatoes[x][y] + 1;
            q.push({x + 1, y});
        }

        if (y > 0 && !tomatoes[x][y - 1]) {
            tomatoes[x][y - 1] = tomatoes[x][y] + 1;
            q.push({x, y - 1});
        }

        if (y < tomatoes[0].size() - 1 && !tomatoes[x][y + 1]) {
            tomatoes[x][y + 1] = tomatoes[x][y] + 1;
            q.push({x, y + 1});
        }
    }

    for (const auto& row : tomatoes)
        for (const auto& tomatoe : row)
            if (!tomatoe) return -1;

    return days - 1;
}

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    unsigned n, m;
    std::cin >> n >> m;

    std::vector<std::vector<int>> tomatoes(m, std::vector<int>(n));
    std::queue<std::pair<unsigned, unsigned>> q;

    for (unsigned i = 0; i < m; ++i)
        for (unsigned j = 0; j < n; ++j) {
            std::cin >> tomatoes[i][j];
            if (tomatoes[i][j] == 1) q.push({i, j});
        }

    std::cout << bfs(tomatoes, q);

    return 0;
}