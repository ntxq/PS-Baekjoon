#include <algorithm>
#include <iostream>
#include <limits>
#include <numeric>
#include <vector>

template <typename T>
using Matrix = std::vector<std::vector<T>>;

std::pair<int, int> getNext(int x, int y, char move) {
    switch (move) {
        case 'U':
            return {x - 1, y};

        case 'R':
            return {x, y + 1};

        case 'D':
            return {x + 1, y};

        case 'L':
            return {x, y - 1};

        default:
            return {-1, -1};
    }
}

bool dfs(int x, int y, Matrix<bool>& visited, Matrix<bool>& escapable,
         const int N, const int M, const Matrix<char>& board) {
    visited[x][y] = true;

    auto [nx, ny] = getNext(x, y, board[x][y]);
    if (nx < 0 || nx >= N || ny < 0 || ny >= M) return escapable[x][y] = true;
    if (visited[nx][ny]) return escapable[x][y] = escapable[nx][ny];

    return escapable[x][y] = dfs(nx, ny, visited, escapable, N, M, board);
}

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    int N, M;
    std::cin >> N >> M;

    Matrix<char> board(N, std::vector<char>(M));
    for (auto& row : board)
        for (auto& cell : row) std::cin >> cell;

    Matrix<bool> visited(N, std::vector<bool>(M));
    Matrix<bool> escapable(N, std::vector<bool>(M));

    for (int i = 0; i < N; ++i)
        for (int j = 0; j < M; ++j)
            if (!visited[i][j]) dfs(i, j, visited, escapable, N, M, board);

    int count = 0;
    for (int i = 0; i < N; ++i)
        for (int j = 0; j < M; ++j)
            if (escapable[i][j]) ++count;

    std::cout << count << '\n';

    return 0;
}
