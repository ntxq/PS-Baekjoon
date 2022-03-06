#include <algorithm>
#include <iostream>
#include <numeric>
#include <optional>
#include <string>
#include <vector>

bool isPalindrome(int i, int j, const std::string& s) {
    static std::vector<std::vector<std::optional<bool>>> dp(
        s.size(), std::vector<std::optional<bool>>(s.size()));

    if (i == j) return true;
    if (i > j) return true;
    if (dp[i][j].has_value()) return dp[i][j].value();

    return (dp[i][j] = s[i] == s[j] && isPalindrome(i + 1, j - 1, s)).value();
}

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    std::string s;
    std::cin >> s;

    std::vector<int> count(s.size());

    for (unsigned i = 0; i < s.size(); ++i) {
        if (isPalindrome(0, i, s)) count[i] = 1;
        else count[i] = count[i - 1] + 1;

        for (unsigned j = 1; j < i; ++j) {
            int curCount = count[j - 1] + 1;
            if (isPalindrome(j, i, s) && curCount < count[i])
                count[i] = curCount;
        }
    }

    std::cout << count.back() << '\n';

    return 0;
}
