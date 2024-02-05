#include <algorithm>
#include <iostream>
#include <queue>
#include <vector>

bool is_before(const std::tuple<int, int, int>& lhs,
               const std::tuple<int, int, int>& rhs) {
    const auto& [r1, c1, f1] = lhs;
    const auto& [r2, c2, f2] = rhs;
    return (r1 <= r2) && (c1 <= c2);
}

int dist(std::tuple<int, int, int> lhs, std::tuple<int, int, int> rhs) {
    const auto& [r1, c1, f1] = lhs;
    const auto& [r2, c2, f2] = rhs;
    return std::abs(r1 - r2) + std::abs(c1 - c2);
}

bool is_reachable(int R, int C,
                  const std::vector<std::tuple<int, int, int>>& fuels) {
    std::vector<int> dp(fuels.size(), -1);
    dp[0] = std::get<2>(fuels[0]);

    for (int i = 1; i < fuels.size(); ++i)
        for (int j = 0; j < i; ++j)
            if (is_before(fuels[j], fuels[i]) &&
                dp[j] >= dist(fuels[j], fuels[i]))
                dp[i] = std::max(dp[i], dp[j] - dist(fuels[j], fuels[i]) +
                                            std::get<2>(fuels[i]));

    bool ret = false;
    for (int i = 0; i < dp.size(); ++i) {
        const auto& [r, c, f] = fuels[i];
        if (dp[i] != -1 && dp[i] >= (R + C - r - c)) ret = true;
    }

    return ret;
}

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    int R, C;
    std::cin >> R >> C;
    --R, --C;

    int N;
    std::cin >> N;

    std::vector<std::tuple<int, int, int>> fuels(N);
    for (auto& [r, c, f] : fuels) {
        std::cin >> r >> c >> f;
        --r, --c;
    }
    fuels.push_back({0, 0, 0});

    std::sort(fuels.begin(), fuels.end(), [](const auto& lhs, const auto& rhs) {
        const auto& [r1, c1, f1] = lhs;
        const auto& [r2, c2, f2] = rhs;
        return (r1 + c1) < (r2 + c2);
    });

    int low = 1, high = R + C;
    while (low < high) {
        int mid = (low + high) / 2;
        fuels[0] = {0, 0, mid};
        if (is_reachable(R, C, fuels))
            high = mid;
        else
            low = mid + 1;
    }

    std::cout << low << '\n';

    return 0;
}
