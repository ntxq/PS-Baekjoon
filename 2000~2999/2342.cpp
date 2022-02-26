#include <algorithm>
#include <iostream>
#include <limits>
#include <map>
#include <numeric>
#include <vector>

int moveCost(int from, int to) {
    if (from == to)
        return 1;
    else if (from == 0)
        return 2;
    else if (from % 2 != to % 2)
        return 3;
    else
        return 4;
}

int solveDDR(int l, int r, unsigned n, const std::vector<int>& moves) {
    static std::vector<std::vector<std::vector<int>>> dp(5, std::vector<std::vector<int>>(5, std::vector<int>(moves.size())));

    if (n == moves.size())
        return 0;
    if (dp[l][r][n])
        return dp[l][r][n];
    
    return dp[l][r][n] = std::min(
        solveDDR(moves[n], r, n + 1, moves) + moveCost(l, moves[n]),
        solveDDR(l, moves[n], n + 1, moves) + moveCost(r, moves[n])
    );
}

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    std::vector<int> moves;
    for (int move; std::cin >> move && move;) moves.push_back(move);

    std::cout << solveDDR(0, 0, 0, moves) << '\n';

    return 0;
}
