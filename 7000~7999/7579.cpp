#include <algorithm>
#include <iostream>
#include <limits>
#include <vector>

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    int n, m;
    std::cin >> n >> m;

    std::vector<int> memory(n);
    for (int& i : memory) std::cin >> i;

    int totalCost = 0;
    std::vector<int> cost(n);
    for (int& i : cost) {
        std::cin >> i;
        totalCost += i;
    }

    std::vector<int> dp(totalCost + 1);

    for (int i = 0; i < n; ++i)
        for (int j = totalCost; j >= cost[i]; --j)
            if (int curM = dp[j - cost[i]] + memory[i]; curM > dp[j])
                dp[j] = curM;

    std::cout << std::lower_bound(dp.cbegin(), dp.cend(), m) - dp.cbegin()
              << '\n';

    return 0;
}