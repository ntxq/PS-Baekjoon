#include <algorithm>
#include <iostream>
#include <queue>
#include <vector>

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    int n, m;
    std::cin >> n >> m;

    std::vector<std::vector<int>> edges(n);
    std::vector<int> inDegrees(n);
    for (int i = 0; i < m; ++i) {
        int u, v;
        std::cin >> u >> v;

        edges[u - 1].push_back(v - 1);
        ++inDegrees[v - 1];
    }

    std::priority_queue<int, std::vector<int>, std::greater<int>> pq;
    for (int i = 0; i < n; ++i)
        if (!inDegrees[i]) pq.push(i);

    while (!pq.empty()) {
        int u = pq.top();
        pq.pop();

        std::cout << u + 1 << ' ';
        for (int v : edges[u])
            if (!--inDegrees[v]) pq.push(v);
    }

    return 0;
}
