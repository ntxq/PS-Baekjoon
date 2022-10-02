#include <algorithm>
#include <iostream>
#include <vector>

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    int N;
    std::cin >> N;

    std::vector<std::pair<int, int>> schedules(N);
    for (auto& i : schedules) std::cin >> i.first >> i.second;

    std::vector<int> dp(N + 1);

    for (int i = 0; i < N; ++i) {
        auto [t, p] = schedules[i];
        if (i) dp[i] = std::max(dp[i], dp[i - 1]);
        if (i + t <= N) dp[i + t] = std::max(dp[i + t], dp[i] + p);
    }

    std::cout << *std::max_element(dp.begin(), dp.end()) << '\n';

    return 0;
}