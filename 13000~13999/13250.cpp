#include <algorithm>
#include <array>
#include <iomanip>
#include <iostream>
#include <limits>
#include <numeric>
#include <string>
#include <vector>

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    std::vector<double> dp(1000001);
    for (int i = 1; i <= 1000000; ++i) {
        for (int j = 1; j <= 6; ++j) dp[i] += ((i >= j) ? dp[i - j] : 0) + 1;
        dp[i] /= 6;
    }

    int N;
    std::cin >> N;

    std::cout << std::fixed << std::setprecision(10) << dp[N] << '\n';

    return 0;
}
