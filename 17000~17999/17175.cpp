#include <algorithm>
#include <iostream>
#include <limits>
#include <numeric>
#include <queue>
#include <string>
#include <vector>

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    std::vector<long long> dp(51);
    dp[0] = dp[1] = 1;

    for (int i = 2; i < 51; ++i) dp[i] = (dp[i - 1] + dp[i - 2] + 1) % 1000000007;

    int n;
    std::cin >> n;
    std::cout << dp[n] << '\n';

    return 0;
}
