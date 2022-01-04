#include <algorithm>
#include <iostream>
#include <vector>

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    int n, m;
    std::cin >> n >> m;

    std::vector<std::vector<int>> board(n, std::vector<int>(n));
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j) {
            std::cin >> board[i][j];

            if (i && j)
                board[i][j] +=
                    board[i - 1][j] + board[i][j - 1] - board[i - 1][j - 1];
            else if (i)
                board[i][j] += board[i - 1][j];
            else if (j)
                board[i][j] += board[i][j - 1];
        }

    for (int i = 0; i < m; ++i) {
        int x1, y1, x2, y2;
        std::cin >> x1 >> y1 >> x2 >> y2;

        --x1, --y1, --x2, --y2;

        int sum = board[x2][y2];
        if (x1) sum -= board[x1 - 1][y2];
        if (y1) sum -= board[x2][y1 - 1];
        if (x1 && y1) sum += board[x1 - 1][y1 - 1];

        std::cout << sum << '\n';
    }

    return 0;
}