#include <algorithm>
#include <iostream>
#include <limits>
#include <numeric>
#include <string>
#include <vector>

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    std::vector<int> dp(11);
    for (int i = 2; i < 11; ++i) {
        int x = i / 2;
        int y = i - x;
        dp[i] = dp[x] + dp[y] + x * y;
    }

    int n;
    std::cin >> n;
    std::cout << dp[n] << '\n';

    return 0;
}
