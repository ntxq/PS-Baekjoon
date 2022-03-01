#include <algorithm>
#include <bit>
#include <iostream>
#include <vector>

unsigned long long countOne(unsigned long long x,
                            std::vector<unsigned long long>& dp) {
    unsigned long long count = x & 1;
    unsigned index = 55;
    while (--index) {
        if (unsigned long long curBit = 1ULL << index; x & curBit) {
            x &= ~curBit;
            count += dp[index - 1] + (x + 1);
        }
    }

    return count;
}

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    unsigned long long a, b;
    std::cin >> a >> b;

    std::vector<unsigned long long> dp(55);
    dp[0] = 1;
    for (unsigned i = 1; i < 55; ++i)
        dp[i] = 2 * dp[i - 1] + (1ULL << i);

    std::cout << countOne(b, dp) - countOne(a - 1, dp) << '\n';

    return 0;
}
