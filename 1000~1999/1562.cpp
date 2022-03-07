#include <algorithm>
#include <iostream>
#include <numeric>
#include <optional>
#include <string>
#include <vector>

unsigned long long countSteps(int level, int maxLevel, int digit,
                              unsigned visited) {
    static std::vector<std::vector<std::vector<unsigned long long>>> dp(
        maxLevel + 1, std::vector<std::vector<unsigned long long>>(
                          10, std::vector<unsigned long long>(1 << 10)));

    if (dp[level][digit][visited]) return dp[level][digit][visited];
    if (level == maxLevel)
        return (visited == (1 << 10) - 1);

    int count = 0;
    if (digit + 1 < 10)
        count += countSteps(level + 1, maxLevel, digit + 1,
                            visited | 1 << (digit + 1));
    if (digit - 1 >= 0)
        count += countSteps(level + 1, maxLevel, digit - 1,
                            visited | 1 << (digit - 1));

    return dp[level][digit][visited] = count %= 1000000000;
}

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    int n;
    std::cin >> n;

    unsigned long long count = 0;
    for (int i = 1; i < 10; ++i)
        count = (count + countSteps(1, n, i, 1 << i)) % 1000000000;

    std::cout << count << '\n';

    return 0;
}
