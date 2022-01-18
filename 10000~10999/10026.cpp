#include <algorithm>
#include <iostream>
#include <queue>
#include <utility>

std::pair<int, int> bfs(int n, const std::vector<std::vector<char>>& picture) {
    std::vector<std::vector<bool>> visited(n, std::vector<bool>(n));
    std::vector<std::vector<bool>> visitedRG(n, std::vector<bool>(n));

    std::queue<std::pair<int, int>> q;
    std::queue<std::pair<int, int>> qRG;

    int count = 0;
    int countRG = 0;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (!visited[i][j]) {
                q.push({i, j});
                visited[i][j] = true;
                ++count;
            }

            if (!visitedRG[i][j]) {
                qRG.push({i, j});
                visitedRG[i][j] = true;
                ++countRG;
            }

            while (!q.empty()) {
                auto [x, y] = q.front();
                q.pop();

                if (x > 0 && !visited[x - 1][y] &&
                    picture[x - 1][y] == picture[x][y]) {
                    q.push({x - 1, y});
                    visited[x - 1][y] = true;
                }

                if (x < n - 1 && !visited[x + 1][y] &&
                    picture[x + 1][y] == picture[x][y]) {
                    q.push({x + 1, y});
                    visited[x + 1][y] = true;
                }

                if (y > 0 && !visited[x][y - 1] &&
                    picture[x][y - 1] == picture[x][y]) {
                    q.push({x, y - 1});
                    visited[x][y - 1] = true;
                }

                if (y < n - 1 && !visited[x][y + 1] &&
                    picture[x][y + 1] == picture[x][y]) {
                    q.push({x, y + 1});
                    visited[x][y + 1] = true;
                }
            }

            while (!qRG.empty()) {
                auto [x, y] = qRG.front();
                qRG.pop();

                if (x > 0 && !visitedRG[x - 1][y] &&
                    (picture[x - 1][y] == picture[x][y] ||
                     (picture[x - 1][y] != 'B' && picture[x][y] != 'B'))) {
                    qRG.push({x - 1, y});
                    visitedRG[x - 1][y] = true;
                }

                if (x < n - 1 && !visitedRG[x + 1][y] &&
                    (picture[x + 1][y] == picture[x][y] ||
                     (picture[x + 1][y] != 'B' && picture[x][y] != 'B'))) {
                    qRG.push({x + 1, y});
                    visitedRG[x + 1][y] = true;
                }

                if (y > 0 && !visitedRG[x][y - 1] &&
                    (picture[x][y - 1] == picture[x][y] ||
                     (picture[x][y - 1] != 'B' && picture[x][y] != 'B'))) {
                    qRG.push({x, y - 1});
                    visitedRG[x][y - 1] = true;
                }

                if (y < n - 1 && !visitedRG[x][y + 1] &&
                    (picture[x][y + 1] == picture[x][y] ||
                     (picture[x][y + 1] != 'B' && picture[x][y] != 'B'))) {
                    qRG.push({x, y + 1});
                    visitedRG[x][y + 1] = true;
                }
            }
        }
    }

    return {count, countRG};
}

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    int n;
    std::cin >> n;

    std::vector<std::vector<char>> picture(n, std::vector<char>(n));
    for (auto& i : picture)
        for (auto& j : i) std::cin >> j;

    std::cout << bfs(n, picture).first << ' ' << bfs(n, picture).second;

    return 0;
}