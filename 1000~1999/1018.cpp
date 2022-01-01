#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

int countRecolor(const std::vector<std::string>& board, int x, int y,
                 char start) {
    int count = 0;
    for (int i = x; i < x + 8; ++i) {
        for (int j = y; j < y + 8; ++j) {
            if (board[i][j] != start) ++count;
            start = start == 'W' ? 'B' : 'W';
        }
        start = start == 'W' ? 'B' : 'W';
    }

    return count;
}

int findMinRecolor(const std::vector<std::string>& board) {
    int min = 64;
    for (unsigned int i = 0; i < board.size() - 7; ++i) {
        for (unsigned int j = 0; j < board[0].size() - 7; ++j) {
            min = std::min({min, countRecolor(board, i, j, 'W'),
                            countRecolor(board, i, j, 'B')});
        }
    }

    return min;
}

int main() {
    int n, m;
    std::cin >> n >> m;

    std::vector<std::string> v;
    for (int i = 0; i < n; ++i) {
        std::string s;
        std::cin >> s;
        v.push_back(s);
    }

    std::cout << findMinRecolor(v);

    return 0;
}