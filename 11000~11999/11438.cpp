#include <algorithm>
#include <iostream>
#include <vector>

int find(int x, std::vector<int>& parents) {
    int root = x;
    while (parents[root] != root) root = parents[root];

    while (parents[x] != root) {
        int next = parents[x];
        parents[x] = root;
        x = next;
    }

    return root;
}

void unite(int x, int y, std::vector<int>& parents) {
    static std::vector<int> ranks(parents.size());

    int xroot = find(x, parents);
    int yroot = find(y, parents);

    if (xroot != yroot) {
        if (ranks[xroot] == ranks[yroot]) {
            parents[xroot] = yroot;
            ranks[yroot]++;
        } else if (ranks[xroot] < ranks[yroot]) {
            parents[xroot] = yroot;
        } else {
            parents[yroot] = xroot;
        }
    }
}

void tarjanOLCA(int v, std::vector<int>& lca,
                const std::vector<std::vector<std::pair<int, int>>>& query,
                const std::vector<std::vector<int>>& graph) {
    static std::vector<int> ancestors(graph.size());
    static std::vector<int> parents(graph.size());

    ancestors[v] = v;
    parents[v] = v;

    for (int u : graph[v]) {
        if (!ancestors[u]) {
            tarjanOLCA(u, lca, query, graph);
            unite(u, v, parents);
            ancestors[find(v, parents)] = v;
        }
    }

    for (auto [u, i] : query[v])
        if (ancestors[u] && !lca[i]) lca[i] = ancestors[find(u, parents)];
}

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    int n;
    std::cin >> n;

    std::vector<std::vector<int>> graph(n + 1);
    for (int i = 1; i < n; ++i) {
        int u, v;
        std::cin >> u >> v;

        graph[u].push_back(v);
        graph[v].push_back(u);
    }

    int m;
    std::cin >> m;

    std::vector<std::vector<std::pair<int, int>>> query(n + 1);
    std::vector<int> lca(m);

    for (int i = 0; i < m; ++i) {
        int u, v;
        std::cin >> u >> v;

        query[u].push_back({v, i});
        query[v].push_back({u, i});
    }

    tarjanOLCA(1, lca, query, graph);

    for (int i : lca) std::cout << i << '\n';

    return 0;
}
