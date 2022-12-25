#include <iostream>
#include <stack>
#include <vector>

bool dfs(int root, const std::vector<std::vector<int>>& adj,
         const std::vector<int>& order) {
    std::stack<int> s;
    std::vector<int> traversal;
    std::vector<bool> visited(adj.size());
    s.push(root);

    while (!s.empty()) {
        int u = s.top();
        s.pop();

        if (!visited[u]) {
            visited[u] = true;
            traversal.push_back(u);

            for (int v : adj[u])
                if (!visited[v]) s.push(v);
        }
    }

    for (unsigned i = 0; i < traversal.size(); ++i)
        if (traversal[i] != order[i]) return false;
    return true;
}

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    int N;
    std::cin >> N;

    std::vector<std::vector<int>> adj(N + 1);
    for (int i = 1; i < N; ++i) {
        int u, v;
        std::cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    std::vector<int> priority(N + 1);
    std::vector<int> order;
    for (int i = 0; i < N; ++i) {
        int x;
        std::cin >> x;
        priority[x] = i;
        order.push_back(x);
    }

    std::for_each(adj.begin(), adj.end(), [&](auto& v) {
        std::sort(v.begin(), v.end(),
                  [&](int a, int b) { return priority[a] > priority[b]; });
    });

    std::cout << dfs(1, adj, order) << '\n';

    return 0;
}
