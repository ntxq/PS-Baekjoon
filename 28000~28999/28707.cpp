#include <algorithm>
#include <iostream>
#include <limits>
#include <map>
#include <numeric>
#include <queue>
#include <vector>

int dijkstra(const std::vector<int>& A,
             const std::vector<std::tuple<int, int, int>>& ops) {
    using T = std::pair<int, std::vector<int>>;
    std::priority_queue<T, std::vector<T>, std::greater<T>> pq;
    std::map<std::vector<int>, int> visited;

    pq.push({0, A});
    visited.insert({A, 0});

    while (!pq.empty()) {
        auto [cost, u] = pq.top();
        pq.pop();

        if (std::ranges::is_sorted(u)) return cost;

        for (const auto& [l, r, c] : ops) {
            std::vector<int> v = u;
            std::swap(v[l], v[r]);

            if (!visited.contains(v) || cost + c < visited[v]) {
                pq.push({cost + c, v});
                visited[v] = cost + c;
            }
        }
    }

    return -1;
}

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    int N;
    std::cin >> N;

    std::vector<int> A(N);
    for (int& a : A) std::cin >> a;

    int M;
    std::cin >> M;

    std::vector<std::tuple<int, int, int>> ops(M);
    for (auto& [l, r, x] : ops) {
        std::cin >> l >> r >> x;
        --l, --r;
    }

    std::cout << dijkstra(A, ops) << '\n';

    return 0;
}
