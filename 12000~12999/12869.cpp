#include <algorithm>
#include <iostream>
#include <vector>

/*
Subproblem
    dp[i][j][k] = # of attacks to kill all enemies with i,j,k health each

Relation
    dp[i][j][k] = min(dp[i-a][j-b][k-c]) + 1 for a,b,c in {9,3,1}

Topological Order
    i,j,k from 0 to 60

Base Case
    dp[0][0][0] = 0

Original Problem
    dp[x][y][z] where case n <= 3 is y or z = 0

Time Complexity
    O(n^3)
*/

using DP = std::vector<std::vector<std::vector<int>>>;

std::tuple<int, int, int> getNext(int a, int b, int c) {
    if (a < 0) a = 0;
    if (b < 0) b = 0;
    if (c < 0) c = 0;

    int max = std::max({a, b, c});
    int min = std::min({a, b, c});
    int mid = a + b + c - max - min;

    return {max, mid, min};
}

DP getDP() {
    DP dp(61, std::vector<std::vector<int>>(61, std::vector<int>(61)));

    dp[0][0][0] = 0;
    for (int i = 0; i < 61; ++i)
        for (int j = 0; j <= i; ++j)
            for (int k = 0; k <= j; ++k)
                if (i || j || k) {
                    // case 9, 3, 1
                    auto [a1, b1, c1] = getNext(i - 9, j - 3, k - 1);

                    // case 9, 1, 3
                    auto [a2, b2, c2] = getNext(i - 9, j - 1, k - 3);

                    // case 3, 9, 1
                    auto [a3, b3, c3] = getNext(i - 3, j - 9, k - 1);

                    // case 1, 9, 3
                    auto [a4, b4, c4] = getNext(i - 1, j - 9, k - 3);

                    // case 3, 1, 9
                    auto [a5, b5, c5] = getNext(i - 3, j - 1, k - 9);

                    // case 1, 3, 9
                    auto [a6, b6, c6] = getNext(i - 1, j - 3, k - 9);

                    dp[i][j][k] = std::min({dp[a1][b1][c1], dp[a2][b2][c2],
                                            dp[a3][b3][c3], dp[a4][b4][c4],
                                            dp[a5][b5][c5], dp[a6][b6][c6]}) +
                                  1;
                }

    return dp;
}

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    int N;
    std::cin >> N;

    int scv[3] = {0, 0, 0};
    for (int i = 0; i < N; ++i) std::cin >> scv[i];

    auto [a, b, c] = getNext(scv[0], scv[1], scv[2]);
    auto dp = getDP();  
    std::cout << dp[a][b][c] << '\n';

    return 0;
}
