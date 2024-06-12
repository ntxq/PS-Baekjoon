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

    std::vector<std::pair<int, int>> lines(N);
    for (auto& [a, b] : lines) std::cin >> a >> b;

    std::sort(lines.begin(), lines.end());

    int maxOverlap = 0;
    std::priority_queue<int, std::vector<int>, std::greater<int>> pq;
    for (int i = 0; i < N; ++i) {
        auto [a, b] = lines[i];

        while (!pq.empty() && pq.top() <= a) pq.pop();
        pq.push(b);

        maxOverlap = std::max(maxOverlap, static_cast<int>(pq.size()));
    }

    std::cout << maxOverlap << '\n';

    return 0;
}
