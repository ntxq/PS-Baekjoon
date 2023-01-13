#include <algorithm>
#include <iostream>
#include <numeric>
#include <unordered_set>
#include <vector>

int N, M;
std::vector<std::vector<bool>> visited;
std::vector<std::vector<char>> board;

struct Cross {
    int x, y, s;
};

bool isAllCrossPlaced() {
    return std::all_of(visited.begin(), visited.end(),
                       [](const std::vector<bool>& row) {
                           return std::all_of(row.begin(), row.end(),
                                              [](bool v) { return v; });
                       });
}

int findMaxCross(int r, int c) {
    int x = r, y = c;

    int s = 0;
    bool isValid = board[x][y] == '*';

    int dx[] = {0, 1, 0, -1};
    int dy[] = {1, 0, -1, 0};
    while (isValid) {
        ++s;
        for (int i = 0; i < 4 && isValid; ++i) {
            int nx = x + dx[i] * s;
            int ny = y + dy[i] * s;

            if (nx < 0 || nx >= N || ny < 0 || ny >= M || board[nx][ny] != '*')
                isValid = false;
        }
    }

    return s - 1;
}

void tryCross(int x, int y, int s) {
    int dx[] = {0, 1, 0, -1};
    int dy[] = {1, 0, -1, 0};
    for (int i = 1; i <= s; ++i)
        for (int j = 0; j < 4; ++j)
            visited[x + dx[j] * i][y + dy[j] * i] = true;
    visited[x][y] = true;
}

bool placeCross(int idx, std::vector<Cross>& crosses) {
    if (idx == N * M) return isAllCrossPlaced();

    int r = idx / M;
    int c = idx % M;

    if (board[r][c] == '.') {
        visited[r][c] = true;
        return placeCross(idx + 1, crosses);
    }

    if (int s = findMaxCross(r, c)) {
        tryCross(r, c, s);
        crosses.push_back({r, c, s});
        return placeCross(idx + 1, crosses);
    }

    return placeCross(idx + 1, crosses);
}

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    std::cin >> N >> M;

    visited.assign(N, std::vector<bool>(M));
    board.assign(N, std::vector<char>(M));

    for (int i = 0; i < N; ++i)
        for (int j = 0; j < M; ++j) std::cin >> board[i][j];

    std::vector<Cross> crosses;
    if (placeCross(0, crosses)) {
        std::cout << crosses.size() << '\n';
        for (const auto& c : crosses)
            std::cout << c.x + 1 << ' ' << c.y + 1 << ' ' << c.s << '\n';
    } else {
        std::cout << -1 << '\n';
    }

    return 0;
}