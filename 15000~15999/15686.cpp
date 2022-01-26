#include <cmath>
#include <iostream>
#include <queue>
#include <tuple>
#include <utility>
#include <vector>

int chickenDist(const std::vector<std::pair<int, int>>& houses,
                const std::vector<std::tuple<int, int, bool>>& chickens) {
    int sumDist = 0;
    for (unsigned i = 0; i < houses.size(); ++i) {
        int minDist = 0;
        const auto& [x, y] = houses[i];

        for (unsigned j = 0; j < chickens.size(); ++j) {
            const auto& [cx, cy, isValid] = chickens[j];
            if (int curDist = std::abs(cx - x) + std::abs(cy - y);
                isValid && (curDist < minDist || minDist == 0))
                minDist = curDist;
        }

        sumDist += minDist;
    }

    return sumDist;
}

int backtrack(unsigned level, int target,
              const std::vector<std::pair<int, int>>& houses,
              std::vector<std::tuple<int, int, bool>>& chickens) {
    if (!target) return chickenDist(houses, chickens);

    int minDist = 0;
    for (unsigned i = level; i < chickens.size() - target + 1; ++i) {
        auto& [x, y, isValid] = chickens[i];
        isValid = false;

        if (int curDist = backtrack(i + 1, target - 1, houses, chickens);
            curDist < minDist || !minDist)
            minDist = curDist;

        isValid = true;
    }

    return minDist;
}

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    int n, m;
    std::cin >> n >> m;

    std::vector<std::pair<int, int>> houses;
    std::vector<std::tuple<int, int, bool>> chickens;

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            int cell;
            std::cin >> cell;

            if (cell == 1)
                houses.push_back({i, j});
            else if (cell == 2)
                chickens.push_back({i, j, true});
        }
    }

    std::cout << backtrack(0, chickens.size() - m, houses, chickens);

    return 0;
}