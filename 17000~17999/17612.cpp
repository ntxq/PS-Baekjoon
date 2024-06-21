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

    // Time, Node
    std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>,
                        std::greater<>>
        pq_in;
    for (int i = 0; i < K; ++i) pq_in.push({0, i});

    // Time, -Node, Customer
    std::priority_queue<std::tuple<int, int, int>,
                        std::vector<std::tuple<int, int, int>>, std::greater<>>
        pq_out;

    for (int i = 0; i < N; ++i) {
        int id, w;
        std::cin >> id >> w;

        auto [time, node] = pq_in.top();
        pq_in.pop();
        pq_in.push({time + w, node});

        pq_out.push({time + w, -node, id});
    }

    long long res = 0;
    long long cnt = 0;
    while (!pq_out.empty()) {
        auto [time, node, id] = pq_out.top();
        pq_out.pop();

        res += ++cnt * id;
    }

    std::cout << res << '\n';

    return 0;
}
