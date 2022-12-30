#include <iostream>
#include <queue>
#include <vector>

void bfs(const std::vector<std::vector<int>>& board,
         std::vector<std::vector<int>>& visited, std::vector<int>& sizes,
         int sx, int sy) {
    std::queue<std::pair<int, int>> q;

    q.push({sx, sy});
    sizes.push_back(1);
    visited[sx][sy] = sizes.size();

    int dx[] = {0, -1, 0, 1};
    int dy[] = {-1, 0, 1, 0};

    while (!q.empty()) {
        auto [x, y] = q.front();
        q.pop();

        for (int i = 0; i < 4; ++i) {
            int nx = x + dx[i];
            int ny = y + dy[i];
            bool isValid = !(board[x][y] & (1 << i));

            if (isValid && !visited[nx][ny]) {
                q.push({nx, ny});
                visited[nx][ny] = visited[x][y];
                ++sizes.back();
            }
        }
    }
}

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    int N, M;
    std::cin >> N >> M;

    std::vector<std::vector<int>> board(M, std::vector<int>(N));
    for (auto& row : board)
        for (auto& cell : row) std::cin >> cell;

    std::vector<std::vector<int>> visited(M, std::vector<int>(N));
    std::vector<int> sizes;

    for (int i = 0; i < M; ++i)
        for (int j = 0; j < N; ++j)
            if (!visited[i][j]) bfs(board, visited, sizes, i, j);

    std::cout << sizes.size() << '\n';

    std::cout << *std::max_element(sizes.begin(), sizes.end()) << '\n';

    int curMax = 0;
    for (int i = 0; i < M; ++i)
        for (int j = 0; j < N; ++j) {
            if (i != M - 1 && visited[i][j] != visited[i + 1][j])
                curMax = std::max(curMax, sizes[visited[i][j] - 1] +
                                              sizes[visited[i + 1][j] - 1]);
            if (j != N - 1 && visited[i][j] != visited[i][j + 1])
                curMax = std::max(curMax, sizes[visited[i][j] - 1] +
                                              sizes[visited[i][j + 1] - 1]);
        }
    std::cout << curMax << '\n';

    return 0;
}
