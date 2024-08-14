#include <algorithm>
#include <cmath>
#include <iostream>
#include <limits>
#include <numeric>
#include <set>
#include <vector>

bool is_perfect_square(const unsigned long long& n) {
    unsigned long long root = std::sqrt(n);
    return root * root == n;
}

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    std::string s;
    std::cin >> s;

    std::vector<unsigned long long> dp(
        s.size() + 1, std::numeric_limits<unsigned long long>::max());
    dp[0] = 0;

    for (int i = 0; i < s.size(); ++i) {
        if (dp[i] == std::numeric_limits<unsigned long long>::max()) continue;

        unsigned long long curNum = 0;
        for (int j = i; j < s.size() && j - i < 15; ++j) {
            curNum = curNum * 10 + s[j] - '0';
            if (curNum == 0) break;
            if (is_perfect_square(curNum))
                dp[j + 1] = std::min(dp[j + 1], dp[i] + curNum);
        }
    }

        if (dp[s.size()] == std::numeric_limits<unsigned long long>::max() ||
        dp[s.size()] > 1000000000ULL)
        std::cout << -1 << '\n';
    else
        std::cout << dp[s.size()] << '\n';

    return 0;
}
