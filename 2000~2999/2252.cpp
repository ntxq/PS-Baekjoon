#include <iostream>
#include <stack>
#include <vector>

void dfs(const std::vector<std::vector<int>>& adj, std::vector<bool>& visited,
         std::stack<int>& order, int u) {
    if (visited[u]) return;

    visited[u] = true;
    for (int v : adj[u]) dfs(adj, visited, order, v);

    order.push(u);
}

std::stack<int> topologicalSort(const std::vector<std::vector<int>>& adj) {
    std::vector<bool> visited(adj.size());
    std::stack<int> order;

    for (decltype(adj.size()) i = 0; i < adj.size(); ++i)
        if (!visited[i]) dfs(adj, visited, order, i);

    return order;
}

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    int n, m;
    std::cin >> n >> m;

    std::vector<std::vector<int>> adj(n);
    for (int i = 0; i < m; ++i) {
        int u, v;
        std::cin >> u >> v;

        adj[u - 1].push_back(v - 1);
    }

    std::stack<int> order = topologicalSort(adj);
    while (!order.empty()) {
        std::cout << order.top() + 1 << ' ';
        order.pop();
    }

    return 0;
}