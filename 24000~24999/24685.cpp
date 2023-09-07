#include <algorithm>
#include <iostream>
#include <numeric>
#include <vector>

bool is_sorted(const std::vector<std::pair<int, int>>& minions,
               int total_buffs) {
    if (minions.size() <= 2) return true;

    for (int i = 0; i < minions.size() - 1; ++i)
        if (minions[i].first + minions[i].second + total_buffs >
            minions[i + 1].first)
            return false;

    return true;
}

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    int T;
    std::cin >> T;

    while (T--) {
        int N;
        std::cin >> N;

        std::vector<std::pair<int, int>> minions(N);

        for (int i = 0; i < N; ++i) {
            std::cin >> minions[i].first >> minions[i].second;
            minions[i].second *= -1;
        }

        std::sort(minions.begin(), minions.end());

        int total_buffs =
            std::accumulate(minions.begin(), minions.end(), 0,
                            [](int acc, const std::pair<int, int>& minion) {
                                return acc - minion.second;
                            });

        std::cout << (is_sorted(minions, total_buffs) ? "Yes" : "No") << '\n';
    }

    return 0;
}
