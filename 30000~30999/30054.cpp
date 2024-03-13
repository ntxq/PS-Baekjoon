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

    auto compare = [](const std::pair<int, int>& a,
                      const std::pair<int, int>& b) {
        if (a.second != b.second) return a.second > b.second;
        return a.first > b.first;
    };
    std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>,
                        decltype(compare)>
        pq(compare);
    std::vector<int> arrival(400001, std::numeric_limits<int>::max());

    for (int i = 0; i < N; ++i) {
        int x, y;
        std::cin >> x >> y;
        pq.push({x, y});
        arrival[x] = y;
    }

    int cur_time = 1;
    int max_wait = 0;
    while (!pq.empty()) {
        if (arrival[cur_time] <= cur_time) {
            max_wait = std::max(max_wait, cur_time - arrival[cur_time]);
            arrival[cur_time] = std::numeric_limits<int>::max();
        } else if (pq.top().second <= cur_time) {
            auto [x, y] = pq.top();
            pq.pop();

            max_wait = std::max(max_wait, cur_time - y);
            arrival[x] = std::numeric_limits<int>::max();
        }

        while (!pq.empty() &&
               arrival[pq.top().first] == std::numeric_limits<int>::max()) {
            pq.pop();
        }

        ++cur_time;
    }

    std::cout << max_wait << '\n';

    return 0;
}
