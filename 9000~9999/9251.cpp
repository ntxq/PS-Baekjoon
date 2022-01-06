#include <iostream>
#include <string>
#include <vector>

int lcs(const std::string& a, const std::string& b) {
    std::vector<std::vector<int>> dp(a.size() + 1,
                                     std::vector<int>(b.size() + 1, 0));

    for (unsigned i = 1; i <= a.size(); ++i)
        for (unsigned j = 1; j <= b.size(); ++j)
            if (a[i - 1] == b[j - 1])
                dp[i][j] = dp[i - 1][j - 1] + 1;
            else
                dp[i][j] = std::max(dp[i - 1][j], dp[i][j - 1]);

    return dp[a.size()][b.size()];
}

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    std::string a, b;
    std::cin >> a >> b;

    std::cout << lcs(a, b);

    return 0;
}