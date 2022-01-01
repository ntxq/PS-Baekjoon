#include <algorithm>
#include <iostream>
#include <vector>

int countConnected(const std::vector<std::vector<int>>& graph) {
    std::vector<bool> visited(graph.size(), false);
    std::vector<int> s;

    int count = 0;
    for (unsigned i = 0; i < graph.size(); ++i) {
        if (!visited[i]) {
            s.push_back(i);
            visited[i] = true;
            ++count;
        }

        while (!s.empty()) {
            int cur = s.back();
            s.pop_back();

            for (unsigned j = 0; j < graph[cur].size(); ++j) {
                const int& next = graph[cur][j];
                if (!visited[next]) {
                    visited[next] = true;
                    s.push_back(next);
                }
            }
        }
    }

    return count;
}

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    int v, e;
    std::cin >> v >> e;

    std::vector<std::vector<int>> graph(v);
    for (int i = 0; i < e; ++i) {
        int u, v;
        std::cin >> u >> v;

        graph[u - 1].push_back(v - 1);
        graph[v - 1].push_back(u - 1);
    }

    std::cout << countConnected(graph);

    return 0;
}