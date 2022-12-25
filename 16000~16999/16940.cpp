#include <iostream>
#include <queue>
#include <vector>

bool bfs(int root, const std::vector<std::vector<int>>& adj) {
    std::queue<int> q;
    std::vector<int> visited(adj.size());
    bool isValid = true;

    q.push(root);
    visited[root] = 1;
    if (int s; std::cin >> s && s - 1 != root) isValid = false;

    while (!q.empty() && isValid) {
        int u = q.front();
        q.pop();

        int count = 0;
        for (int v : adj[u])
            if (!visited[v]) {
                visited[v] = 1;
                ++count;
            }

        for (int i = 0; i < count && isValid; ++i) {
            int v;
            std::cin >> v;
            --v;

            if (visited[v] == 1) {
                q.push(v);
                visited[v] = 2;
            } else {
                isValid = false;
            }
        }
    }

    return isValid;
}

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    int N;
    std::cin >> N;

    std::vector<std::vector<int>> adj(N);
    for (int i = 1; i < N; ++i) {
        int u, v;
        std::cin >> u >> v;
        --u, --v;

        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    std::cout << bfs(0, adj) << '\n';

    return 0;
}
