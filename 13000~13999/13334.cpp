#include <algorithm>
#include <functional>
#include <iostream>
#include <queue>
#include <utility>
#include <vector>

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    int n;
    std::cin >> n;

    std::vector<std::pair<int, int>> v(n);
    for (auto& i : v) {
        int a, b;
        std::cin >> a >> b;

        if (a < b)
            i = {b, a};
        else
            i = {a, b};
    }
    std::sort(v.begin(), v.end());

    int d;
    std::cin >> d;

    std::priority_queue<int, std::vector<int>, std::greater<int>> pq;
    unsigned maxCount = 0;

    for (const auto& i : v) {
        pq.push(i.second);
        while (!pq.empty() && i.first - pq.top() > d) pq.pop();

        if (pq.size() > maxCount) maxCount = pq.size();
    }

    std::cout << maxCount << '\n';

    return 0;
}
