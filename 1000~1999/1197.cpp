#include <algorithm>
#include <array>
#include <iostream>
#include <numeric>
#include <vector>

int find(std::vector<int>& parent, int x) {
    int root = x;
    while (parent[root] != root) root = parent[root];

    while (parent[x] != root) {
        int p = parent[x];
        parent[x] = root;
        x = p;
    }

    return root;
}

void unite(std::vector<int>& parent, std::vector<int>& rank, int x, int y) {
    int xroot = find(parent, x);
    int yroot = find(parent, y);

    if (xroot != yroot) {
        if (rank[xroot] < rank[yroot]) std::swap(xroot, yroot);
        parent[yroot] = xroot;
        if (rank[xroot] == rank[yroot]) ++rank[xroot];
    }
}

int kruskalMST(std::vector<std::array<int, 3>>& edges, int v) {
    std::vector<int> parent(v);
    std::vector<int> rank(v);
    std::iota(parent.begin(), parent.end(), 0);

    int cost = 0;
    for (const auto& [w, u, v] : edges) {
        if (find(parent, u) != find(parent, v)) {
            unite(parent, rank, u, v);
            cost += w;
        }
    }

    return cost;
}

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    int v, e;
    std::cin >> v >> e;

    std::vector<std::array<int, 3>> edges(e);
    for (int i = 0; i < e; ++i) {
        int u, v, w;
        std::cin >> u >> v >> w;

        edges.push_back({w, u - 1, v - 1});
    }

    std::sort(edges.begin(), edges.end());

    std::cout << kruskalMST(edges, v);

    return 0;
}