#include <functional>
#include <iostream>
#include <queue>
#include <utility>
#include <vector>

unsigned bfs(unsigned start, unsigned target) {
    unsigned visited[100001]{};

    using uPair = std::pair<unsigned, unsigned>;
    std::priority_queue<uPair, std::vector<uPair>, std::greater<uPair>> pq;
    pq.push({1, start});
    visited[start] = 1;

    while (!pq.empty() && !visited[target]) {
        auto [time, cur] = pq.top();
        pq.pop();

        if (cur * 2 < 100001 && !visited[cur * 2]) {
            pq.push({time, cur * 2});
            visited[cur * 2] = time;
        }

        if (cur > 0 && !visited[cur - 1]) {
            pq.push({time + 1, cur - 1});
            visited[cur - 1] = time + 1;
        }

        if (cur < 100000 && !visited[cur + 1]) {
            pq.push({time + 1, cur + 1});
            visited[cur + 1] = time + 1;
        }
    }

    return visited[target] - 1;
}

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    unsigned start, target;
    std::cin >> start >> target;

    std::cout << bfs(start, target);

    return 0;
}