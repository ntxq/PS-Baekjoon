#include <algorithm>
#include <iostream>
#include <limits>
#include <numeric>
#include <queue>
#include <vector>

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    int N, M;
    std::cin >> N >> M;

    std::vector<int> times(N);
    for (int& t : times) std::cin >> t;
    std::sort(times.begin(), times.end());

    std::priority_queue<int> pq;

    while (pq.size() < M && !times.empty()) {
        pq.push(-times.back());
        times.pop_back();
    }

    while (!times.empty()) {
        int t = pq.top();
        pq.pop();
        pq.push(t - times.back());
        times.pop_back();
    }

    int max = std::numeric_limits<int>::min();
    while (!pq.empty()) {
        max = std::max(max, -pq.top());
        pq.pop();
    }

    std::cout << max << '\n';

    return 0;
}
