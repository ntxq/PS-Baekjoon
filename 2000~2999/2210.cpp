#include <algorithm>
#include <iostream>
#include <limits>
#include <numeric>
#include <set>
#include <string>
#include <vector>

void dfs(int x, int y, std::string& acc, std::set<std::string>& words,
         const std::vector<std::vector<char>>& board) {
    if (acc.size() == 6) {
        words.insert(acc);
        return;
    }

    int dx[] = {0, 0, 1, -1};
    int dy[] = {1, -1, 0, 0};

    for (int i = 0; i < 4; ++i) {
        int nx = x + dx[i];
        int ny = y + dy[i];

        if (0 <= nx && nx < 5 && 0 <= ny && ny < 5) {
            acc.push_back(board[nx][ny]);
            dfs(nx, ny, acc, words, board);
            acc.pop_back();
        }
    }

    return;
}

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    std::vector<std::vector<char>> board(5, std::vector<char>(5));
    for (auto& row : board)
        for (auto& cell : row) std::cin >> cell;

    std::set<std::string> words;
    for (int i = 0; i < 5; ++i)
        for (int j = 0; j < 5; ++j) {
            std::string acc{board[i][j]};
            dfs(i, j, acc, words, board);
        }

    std::cout << words.size() << '\n';

    return 0;
}