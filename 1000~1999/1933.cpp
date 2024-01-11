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

    std::priority_queue<std::tuple<int, int, int>,
                        std::vector<std::tuple<int, int, int>>, std::greater<>>
        pq;
    for (int i = 0; i < N; ++i) {
        int l, h, r;
        std::cin >> l >> h >> r;

        pq.push({l, -h, r});
    }

    int curEnd = 0;
    int curHeight = 0;

    while (!pq.empty()) {
        auto [l, h, r] = pq.top();
        h = -h;
        pq.pop();

        if (l > curEnd) {
            if (curHeight != 0) std::cout << curEnd << ' ' << 0 << ' ';
            std::cout << l << ' ' << h << ' ';
            curEnd = r;
            curHeight = h;
        } else if (l == curEnd) {
            if (curHeight != h) std::cout << l << ' ' << h << ' ';
            curEnd = r;
            curHeight = h;
        } else if (h <= curHeight) {
            if (r > curEnd) pq.push({curEnd, -h, r});
        } else if (curEnd > r) {
            std::cout << l << ' ' << h << ' ';
            pq.push({r, -curHeight, curEnd});
            curEnd = r;
            curHeight = h;
        } else {
            std::cout << l << ' ' << h << ' ';
            curEnd = r;
            curHeight = h;
        }
    }

    if (curHeight != 0) std::cout << curEnd << ' ' << 0 << '\n';

    return 0;
}
