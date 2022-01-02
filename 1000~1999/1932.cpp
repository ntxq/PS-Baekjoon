#include <algorithm>
#include <iostream>
#include <vector>

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    int n;
    std::cin >> n;

    std::vector<std::vector<int>> triangle(n);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j <= i; ++j) {
            int tmp;
            std::cin >> tmp;

            triangle[i].push_back(tmp);
        }
    }

    std::vector<int> dp(n);
    for (int i = 0; i < n; ++i) {
        for (int j = i; j >= 0; --j) {
            if (j == 0)
                dp[j] = dp[j] + triangle[i][j];
            else if (j == i)
                dp[j] = dp[j - 1] + triangle[i][j];
            else
                dp[j] = std::max(dp[j - 1], dp[j]) + triangle[i][j];
        }
    }

    std::cout << *std::max_element(dp.cbegin(), dp.cend());

    return 0;
}