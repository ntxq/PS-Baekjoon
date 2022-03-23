#include <algorithm>
#include <iostream>
#include <numeric>
#include <utility>
#include <vector>

struct Edge {
    int v;
    int w;
};

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

void unite(int x, int y, std::vector<int>& parents, std::vector<int>& ranks) {
    int xroot = find(x, parents);
    int yroot = find(y, parents);

    if (xroot != yroot) {
        if (ranks[x] == ranks[y]) {
            parents[xroot] = yroot;
            ranks[yroot]++;
        } else if (ranks[x] < ranks[y]) {
            parents[xroot] = yroot;
        } else {
            parents[yroot] = xroot;
        }
    }
}

void tarjanOLCA(int root, std::vector<int>& parents, std::vector<int>& ranks,
                std::vector<int>& ancestors,
                std::vector<std::vector<std::pair<int, int>>>& edges,
                const std::vector<std::vector<std::pair<int, int>>>& queries,
                std::vector<int>& dist, std::vector<int>& answers) {
    parents[root] = root;
    ancestors[find(root, parents)] = root;

    for (const auto& [v, w] : edges[root]) {
        if (!ancestors[v]) {
            dist[v] = dist[root] + w;
            tarjanOLCA(v, parents, ranks, ancestors, edges, queries, dist,
                       answers);
            unite(v, root, parents, ranks);
            ancestors[find(root, parents)] = root;
        }
    }

    for (auto& [v, i] : queries[root])
        if (ancestors[v] && !answers[i])
            answers[i] =
                dist[root] + dist[v] - 2 * dist[ancestors[find(v, parents)]];
}

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    int n;
    std::cin >> n;

    std::vector<std::vector<std::pair<int, int>>> edges(n + 1);
    for (int i = 0; i < n - 1; ++i) {
        int u, v, w;
        std::cin >> u >> v >> w;

        edges[u].push_back({v, w});
        edges[v].push_back({u, w});
    }

    int m;
    std::cin >> m;

    std::vector<std::vector<std::pair<int, int>>> queries(n + 1);
    for (int i = 0; i < m; ++i) {
        int u, v;
        std::cin >> u >> v;

        queries[u].push_back({v, i});
        queries[v].push_back({u, i});
    }

    std::vector<int> parents(n + 1);
    std::vector<int> ranks(n + 1);
    std::vector<int> ancestors(n + 1);
    std::vector<int> dist(n + 1);
    std::vector<int> answers(m);

    tarjanOLCA(1, parents, ranks, ancestors, edges, queries, dist, answers);

    for (const auto& a : answers) std::cout << a << '\n';

    return 0;
}
