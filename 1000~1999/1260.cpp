#include <iostream>
#include <queue>
#include <stack>
#include <vector>

void dfs(int root, const std::vector<std::vector<bool>>& graph) {
    std::vector<bool> visited(graph.size());
    std::stack<int> s;
    s.push(root);

    while (!s.empty()) {
        int curNode = s.top();
        s.pop();

        if (!visited[curNode]) {
            visited[curNode] = true;
            std::cout << curNode + 1 << ' ';

            for (unsigned i = graph[curNode].size() - 1;
                 i < graph[curNode].size(); --i)
                if (graph[curNode][i] && !visited[i]) s.push(i);
        }
    }
}

void bfs(int root, const std::vector<std::vector<bool>>& graph) {
    std::vector<bool> visited(graph.size());
    std::queue<int> q;

    q.push(root);
    visited[root] = true;

    while (!q.empty()) {
        int curNode = q.front();
        q.pop();

        std::cout << curNode + 1 << ' ';
        for (unsigned i = 0; i < graph[curNode].size(); ++i)
            if (graph[curNode][i] && !visited[i]) {
                q.push(i);
                visited[i] = true;
            }
    }
}

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    int n, m, v;
    std::cin >> n >> m >> v;

    std::vector<std::vector<bool>> adj(n, std::vector<bool>(n));
    for (int i = 0; i < m; ++i) {
        int u, v;
        std::cin >> u >> v;
        adj[u - 1][v - 1] = true;
        adj[v - 1][u - 1] = true;
    }

    dfs(v - 1, adj);
    std::cout << '\n';
    bfs(v - 1, adj);

    return 0;
}