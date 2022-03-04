#include <algorithm>
#include <iostream>
#include <set>
#include <stack>
#include <utility>
#include <vector>

void dfs(int x, int y, const std::vector<std::vector<int>>& grid,
         std::vector<std::vector<int>>& connectedComponents,
         std::vector<int>& componentSizes, int n, int m) {
    std::stack<std::pair<int, int>> s;
    int group = componentSizes.size() + 1;

    s.push({x, y});
    componentSizes.push_back(1);
    connectedComponents[x][y] = group;

    while (!s.empty()) {
        auto [x, y] = s.top();
        s.pop();

        int dx[] = {0, 0, 1, -1};
        int dy[] = {1, -1, 0, 0};

        for (int i = 0; i < 4; ++i) {
            int nx = x + dx[i];
            int ny = y + dy[i];

            if (0 <= nx && nx < n && 0 <= ny && ny < m && !grid[nx][ny] &&
                !connectedComponents[nx][ny]) {
                s.push({nx, ny});
                connectedComponents[nx][ny] = group;
                ++componentSizes[group - 1];
            }
        }
    }
}

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    int n, m;
    std::cin >> n >> m;

    std::vector<std::vector<int>> grid(n, std::vector<int>(m));
    for (auto& row : grid)
        for (auto& col : row) {
            char c;
            std::cin >> c;

            col = c - '0';
        }

    std::vector<std::vector<int>> connectedComponents(n, std::vector<int>(m));
    std::vector<int> componentSizes;

    for (int i = 0; i < n; ++i)
        for (int j = 0; j < m; ++j)
            if (!grid[i][j] && !connectedComponents[i][j])
                dfs(i, j, grid, connectedComponents, componentSizes, n, m);

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (grid[i][j]) {
                std::set<int> components;
                int dx[] = {0, 0, 1, -1};
                int dy[] = {1, -1, 0, 0};

                for (int k = 0; k < 4; ++k) {
                    int nx = i + dx[k];
                    int ny = j + dy[k];

                    if (0 <= nx && nx < n && 0 <= ny && ny < m &&
                        connectedComponents[nx][ny])
                        components.insert(connectedComponents[nx][ny]);
                }

                for (const auto& component : components)
                    grid[i][j] += componentSizes[component - 1];
            }
            std::cout << grid[i][j] % 10;
        }
        std::cout << '\n';
    }
    return 0;
}
