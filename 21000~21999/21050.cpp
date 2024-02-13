#include <algorithm>
#include <iostream>
#include <limits>
#include <vector>

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    int N, W;
    std::cin >> N >> W;

    std::vector<std::tuple<int, int, int>> dams(N);
    for (auto& [d, c, u] : dams) std::cin >> d >> c >> u;

    std::vector<int> dp(N, std::numeric_limits<int>::max());
    for (int i = 0; i < N; ++i) {
        auto [d, c, u] = dams[i];
        --d;
        if (d == -1) {
            dp[i] = std::max({W - u, c - u});
        } else {
            dp[i] = std::max({dp[d] - u, c - u});
        }
    }

    dp.push_back(W);
    std::cout << *std::min_element(dp.begin(), dp.end()) << '\n';

    return 0;
}
