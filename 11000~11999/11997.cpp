#include <algorithm>
#include <iostream>
#include <limits>
#include <vector>

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    int N;
    std::cin >> N;

    std::vector<std::pair<int, int>> cows(N);
    std::vector<int> px(N), py(N);
    for (int i = 0; i < N; ++i) {
        std::cin >> cows[i].first >> cows[i].second;
        px[i] = cows[i].first;
        py[i] = cows[i].second;
    }

    std::sort(px.begin(), px.end());
    std::sort(py.begin(), py.end());
    px.erase(std::unique(px.begin(), px.end()), px.end());
    py.erase(std::unique(py.begin(), py.end()), py.end());

    std::vector<std::vector<int>> board(N, std::vector<int>(N, 0));
    for (int i = 0; i < N; ++i) {
        cows[i].first =
            std::lower_bound(px.begin(), px.end(), cows[i].first) - px.begin();
        cows[i].second =
            std::lower_bound(py.begin(), py.end(), cows[i].second) - py.begin();
        ++board[cows[i].first][cows[i].second];
    }

    for (int i = 0; i < N; ++i)
        for (int j = 0; j < N; ++j)
            if (i && j)
                board[i][j] +=
                    board[i - 1][j] + board[i][j - 1] - board[i - 1][j - 1];
            else if (i)
                board[i][j] += board[i - 1][j];
            else if (j)
                board[i][j] += board[i][j - 1];

    int minCow = std::numeric_limits<int>::max();
    for (int i = 0; i < N; ++i)
        for (int j = 0; j < N; ++j) {
            int curCow = board[i][j];
            curCow = std::max(curCow, board[N - 1][N - 1] - board[N - 1][j] -
                                          board[i][N - 1] + board[i][j]);
            curCow = std::max(curCow, board[i][N - 1] - board[i][j]);
            curCow = std::max(curCow, board[N - 1][j] - board[i][j]);
            minCow = std::min(minCow, curCow);
        }

    std::cout << minCow << '\n';

    return 0;
}
