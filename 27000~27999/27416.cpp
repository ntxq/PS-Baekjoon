#include <algorithm>
#include <iostream>
#include <limits>
#include <numeric>
#include <queue>
#include <vector>

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    int N, K;
    std::cin >> N >> K;

    // Start, End, Idx
    std::vector<std::vector<std::tuple<int, int>>> houses(32);
    for (int i = 0; i < N; ++i) {
        int s, t;
        std::cin >> s >> t;
        houses[s].push_back({t, i});
    }

    std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>,
                        std::greater<>>
        pq;
    std::vector<int> ans(N);

    for (int curDay = 1; curDay <= 31; ++curDay) {
        for (const auto& [t, idx] : houses[curDay]) {
            pq.push({t, idx});
        }

        for (int i = 0; i < K && !pq.empty(); ++i) {
            auto [t, idx] = pq.top();
            pq.pop();
            ans[idx] = curDay;
        }
    }

    for (const auto& day : ans) std::cout << day << '\n';

    return 0;
}
