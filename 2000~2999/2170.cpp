#include <algorithm>
#include <iostream>
#include <limits>
#include <numeric>
#include <queue>
#include <vector>

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    int N;
    std::cin >> N;

    std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>,
                        std::greater<std::pair<int, int>>>
        pq;
    for (int i = 0; i < N; ++i) {
        int u, v;
        std::cin >> u >> v;
        pq.push({u, 1});
        pq.push({v, -1});
    }

    int lastIdx = pq.top().first;
    int curDraw = 0;
    int curSum = 0;

    while (!pq.empty()) {
        auto [x, delta] = pq.top();
        pq.pop();

        if (curDraw > 0)
            curSum += x - lastIdx;

        lastIdx = x;
        curDraw += delta;
    }

    std::cout << curSum << '\n';

    return 0;
}
