#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    std::string s, t;
    std::cin >> s >> t;

    std::vector<std::vector<int>> dp(s.size(), std::vector<int>(t.size()));

    int maxLen = 0;
    for (std::size_t i = 0; i < s.size(); ++i)
        for (std::size_t j = 0; j < t.size(); ++j)
            if (s[i] == t[j]) {
                dp[i][j] = (i && j ? dp[i - 1][j - 1] : 0) + 1;
                if (dp[i][j] > maxLen)
                    maxLen = dp[i][j];
            }

    std::cout << maxLen << '\n';

    return 0;
}
