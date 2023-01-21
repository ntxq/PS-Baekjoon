#include <algorithm>
#include <iostream>
#include <limits>
#include <numeric>
#include <vector>

using std::vector;
using Board = vector<vector<bool>>;
using DP = vector<vector<vector<long long>>>;

void moveHorizontal(int sx, int sy, const int N, DP& dp, const Board& board) {
    int ny = sy + 1;
    if (ny >= N || board[sx][ny]) return;
    dp[sx][ny][0] += dp[sx][sy][0];

    int nx = sx + 1;
    if (nx >= N || board[nx][sy] || board[nx][ny]) return;
    dp[nx][ny][2] += dp[sx][sy][0];
}

void moveVertical(int sx, int sy, const int N, DP& dp, const Board& board) {
    int nx = sx + 1;
    if (nx >= N || board[nx][sy]) return;
    dp[nx][sy][1] += dp[sx][sy][1];

    int ny = sy + 1;
    if (ny >= N || board[sx][ny] || board[nx][ny]) return;
    dp[nx][ny][2] += dp[sx][sy][1];
}

void moveDiagonal(int sx, int sy, const int N, DP& dp, const Board& board) {
    int ny = sy + 1;
    if (ny < N && !board[sx][ny]) dp[sx][ny][0] += dp[sx][sy][2];

    int nx = sx + 1;
    if (nx < N && !board[nx][sy]) dp[nx][sy][1] += dp[sx][sy][2];

    if (nx < N && ny < N && !board[nx][ny] && !board[nx][sy] && !board[sx][ny])
        dp[nx][ny][2] += dp[sx][sy][2];
}

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    int N;
    std::cin >> N;

    Board board(N, vector<bool>(N));
    for (int i = 0; i < N; ++i)
        for (int j = 0; j < N; ++j) {
            bool b;
            std::cin >> b;
            board[i][j] = b;
        }

    DP dp(N, vector<vector<long long>>(N, vector<long long>(3)));

    dp[0][1][0] = 1;

    for (int i = 0; i < N; ++i)
        for (int j = 0; j < N; ++j)
            if (!board[i][j]) {
                moveHorizontal(i, j, N, dp, board);
                moveVertical(i, j, N, dp, board);
                moveDiagonal(i, j, N, dp, board);
            }

    std::cout << dp[N - 1][N - 1][0] + dp[N - 1][N - 1][1] + dp[N - 1][N - 1][2] << '\n';

    return 0;
}