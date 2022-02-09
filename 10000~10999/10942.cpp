#include <algorithm>
#include <iostream>
#include <vector>

bool dp(std::vector<std::vector<bool>>& ans,
        std::vector<std::vector<bool>>& visited, const std::vector<int>& board,
        int a, int b) {
    if (b < a) return true;
    if (visited[a][b]) return ans[a][b];

    visited[a][b] = true;
    if (board[a] != board[b]) return ans[a][b] = false;
    return ans[a][b] = dp(ans, visited, board, a + 1, b - 1);
}

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    int n;
    std::cin >> n;

    std::vector<int> board(n);
    for (int& i : board) std::cin >> i;

    int m;
    std::cin >> m;

    std::vector<std::vector<bool>> ans(n, std::vector<bool>(n));
    std::vector<std::vector<bool>> visited(n, std::vector<bool>(n));
    for (int i = 0; i < n; ++i) {
        ans[i][i] = true;
        visited[i][i] = true;
    }

    for (int i = 0; i < m; ++i) {
        int a, b;
        std::cin >> a >> b;

        std::cout << dp(ans, visited, board, a - 1, b - 1) << '\n';
    }

    return 0;
}