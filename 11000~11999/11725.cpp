#include <algorithm>
#include <iostream>
#include <queue>
#include <vector>

void bfs(std::vector<int>& parents,
         const std::vector<std::vector<int>>& graph) {
    std::queue<int> q;
    parents[1] = 1;
    q.push(1);

    while (!q.empty()) {
        int cur = q.front();
        q.pop();

        for (const int& next : graph[cur]) {
            if (!parents[next]) {
                parents[next] = cur;
                q.push(next);
            }
        }
    }

    return;
}

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    int n;
    std::cin >> n;

    std::vector<std::vector<int>> graph(n + 1);
    for (int i = 1; i < n; ++i) {
        int x, y;
        std::cin >> x >> y;

        graph[x].push_back(y);
        graph[y].push_back(x);
    }

    std::vector<int> parents(n + 1);
    bfs(parents, graph);

    for (unsigned i = 2; i < parents.size(); ++i) {
        std::cout << parents[i] << '\n';
    }

    return 0;
}