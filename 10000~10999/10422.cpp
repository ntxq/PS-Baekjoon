#include <algorithm>
#include <iostream>
#include <vector>

/*
Subproblem
    dp[i] = # of ()-strings of length i

Relation
    dp[i] = dp[i-x] * dp[x-1] for x in [1, i-1]

Topological Order
    1..N

Base Case
    dp[0] = 1

Original Problem
    dp[N]

Time Complexity
    O(N^2)

*/  

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    std::vector<long long> dp(2501);
    dp[0] = 1;

    for (int i = 1; i < 2501; ++i)
        for (int j = 1; j <= i; ++j)
            dp[i] = (dp[i] + (dp[i - j] * dp[j - 1]) % 1000000007) % 1000000007;

    int T;
    std::cin >> T;

    while (T--) {
        int L;
        std::cin >> L;
        std::cout << (L % 2 ? 0 : dp[L / 2]) << '\n';
    }

    return 0;
}
