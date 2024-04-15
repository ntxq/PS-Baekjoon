#include <algorithm>
#include <array>
#include <iostream>
#include <limits>
#include <numeric>
#include <vector>

bool is_same(const std::array<std::array<bool, 3>, 3>& x,
             const std::array<std::array<bool, 3>, 3>& y) {
    for (int i = 0; i < 3; ++i)
        for (int j = 0; j < 3; ++j)
            if (x[i][j] != y[i][j]) return false;
    return true;
}

int backtrack(int idx, std::array<std::array<bool, 3>, 3>& board,
              const std::array<std::array<bool, 3>, 3>& target, int cnt) {
    if (idx == 9) {
        if (is_same(board, target)) return cnt;
        return std::numeric_limits<int>::max();
    }

    int curMin = std::numeric_limits<int>::max();

    int x = idx / 3;
    int y = idx % 3;

    curMin = std::min(curMin, backtrack(idx + 1, board, target, cnt));

    std::array<int, 4> dx{0, 0, 1, -1};
    std::array<int, 4> dy{1, -1, 0, 0};

    board[x][y] = !board[x][y];
    for (int i = 0; i < 4; ++i) {
        int nx = x + dx[i];
        int ny = y + dy[i];
        if (nx < 0 || nx >= 3 || ny < 0 || ny >= 3) continue;
        board[nx][ny] = !board[nx][ny];
    }

    curMin = std::min(curMin, backtrack(idx + 1, board, target, cnt + 1));

    board[x][y] = !board[x][y];
    for (int i = 0; i < 4; ++i) {
        int nx = x + dx[i];
        int ny = y + dy[i];
        if (nx < 0 || nx >= 3 || ny < 0 || ny >= 3) continue;
        board[nx][ny] = !board[nx][ny];
    }

    return curMin;
}

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    int P;
    std::cin >> P;

    while (P--) {
        std::array<std::array<bool, 3>, 3> board{};
        std::array<std::array<bool, 3>, 3> target{};
        for (int i = 0; i < 3; ++i)
            for (int j = 0; j < 3; ++j) {
                char c;
                std::cin >> c;
                target[i][j] = c == '*';
            }

        std::cout << backtrack(0, board, target, 0) << '\n';
    }

    return 0;
}
