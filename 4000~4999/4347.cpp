#include <algorithm>
#include <iostream>
#include <limits>
#include <numeric>
#include <string>
#include <vector>

bool isWin(char c, const std::vector<std::string>& board) {
    for (int i = 0; i < 3; ++i) {
        if (board[i][0] == c && board[i][1] == c && board[i][2] == c)
            return true;

        if (board[0][i] == c && board[1][i] == c && board[2][i] == c)
            return true;
    }

    if (board[0][0] == c && board[1][1] == c && board[2][2] == c) return true;

    if (board[0][2] == c && board[1][1] == c && board[2][0] == c) return true;

    return false;
}

int countChar(char c, const std::vector<std::string>& board) {
    int count = 0;
    for (const auto& row : board)
        count += std::count(row.begin(), row.end(), c);

    return count;
}

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    int T;
    std::cin >> T;

    while (T--) {
        std::vector<std::string> board(3);
        for (auto& row : board) std::cin >> row;

        int xCount = countChar('X', board);
        int oCount = countChar('O', board);

        bool isXWin = isWin('X', board);
        bool isOWin = isWin('O', board);

        if ((xCount == oCount && isOWin && !isXWin) ||
            (xCount == oCount + 1 && isXWin && !isOWin) ||
            ((xCount == oCount || xCount == oCount + 1) && !isXWin && !isOWin))
            std::cout << "yes\n";
        else
            std::cout << "no\n";
    }

    return 0;
}
