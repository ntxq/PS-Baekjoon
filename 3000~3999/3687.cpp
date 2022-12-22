#include <iostream>
#include <string>
#include <vector>

std::string getMaxMatch(int matches) {
    std::string s;
    while (matches > 3) {
        s.append("1");
        matches -= 2;
    }

    if (matches == 3)
        s.append("7");
    else
        s.append("1");

    std::reverse(s.begin(), s.end());
    return s;
}

bool operator<(const std::string& a, const std::string& b) {
    if (b.empty()) return true;

    if (a.size() != b.size()) return a.size() < b.size();

    for (unsigned i = a.size() - 1; i < a.size(); --i)
        if (a[i] != b[i]) return a[i] < b[i];

    return false;
}

std::string getMinMatch(int matches) {
    std::pair<char, int> numbers[10] = {{'1', 2}, {'2', 5}, {'3', 5}, {'4', 4},
                                        {'5', 5}, {'6', 6}, {'7', 3}, {'8', 7},
                                        {'9', 6}, {'0', 6}};

    std::vector<std::string> dp(matches + 1);

    for (int i = 2; i < matches; ++i)
        for (int j = 0; j < 10; ++j) {
            auto [digit, cost] = numbers[j];
            if (cost <= i && i - cost != 1) {
                auto newNumber = dp[i - cost] + digit;
                if (newNumber < dp[i]) dp[i] = newNumber;
            }
        }

    for (int i = 0; i < 9; ++i) {
        auto [digit, cost] = numbers[i];
        if (cost <= matches && matches - cost != 1) {
            auto newNumber = dp[matches - cost] + digit;
            if (newNumber < dp[matches]) dp[matches] = newNumber;
        }
    }

    std::reverse(dp[matches].begin(), dp[matches].end());
    return dp[matches];
}

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    int T;
    std::cin >> T;

    while (T--) {
        int n;
        std::cin >> n;

        std::cout << getMinMatch(n) << ' ' << getMaxMatch(n) << '\n';
    }

    return 0;
}