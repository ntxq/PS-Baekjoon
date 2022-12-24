#include <iostream>
#include <queue>
#include <vector>

int bfs(int rx, int ry, std::vector<std::vector<int>>& color,
        const std::vector<std::vector<bool>>& shouldColor, int N) {
    int numColors = 0;
    std::queue<std::pair<int, int>> q;

    q.push({rx, ry});
    color[rx][ry] = ++numColors;

    int dx[] = {-1, -1, 0, 1, 1, 0};
    int dy[] = {0, 1, 1, 0, -1, -1};

    while (!q.empty()) {
        auto [x, y] = q.front();
        q.pop();

        int nextColor = (color[x][y] == 1) ? 2 : 1;
        for (int i = 0; i < 6; ++i) {
            int nx = x + dx[i];
            int ny = y + dy[i];

            if (0 <= nx && nx < N && 0 <= ny && ny < N && shouldColor[nx][ny]) {
                if (!color[nx][ny]) {
                    q.push({nx, ny});
                    color[nx][ny] = (color[x][y] == 1) ? 2 : 1;
                    numColors = 2;
                } else if (color[nx][ny] != nextColor) {
                    return 3;
                }
            }
        }
    }

    return numColors;
}

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    int N;
    std::cin >> N;

    std::vector<std::vector<bool>> shouldColor(N, std::vector<bool>(N, false));
    for (int i = 0; i < N; ++i)
        for (int j = 0; j < N; ++j) {
            char c;
            std::cin >> c;
            shouldColor[i][j] = c == 'X';
        }

    int numColors = 0;
    std::vector<std::vector<int>> color(N, std::vector<int>(N));

    for (int i = 0; i < N; ++i)
        for (int j = 0; j < N; ++j)
            if (shouldColor[i][j] && !color[i][j]) {
                numColors = std::max(numColors, bfs(i, j, color, shouldColor, N));
            }

    std::cout << numColors << '\n';

    return 0;
}
