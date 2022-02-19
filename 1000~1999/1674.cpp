#include <algorithm>
#include <array>
#include <iostream>
#include <numeric>
#include <queue>

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
        if (rank[xroot] < rank[yroot])
            parent[xroot] = yroot;
        else
            parent[yroot] = xroot;

        if (rank[xroot] == rank[yroot]) ++rank[xroot];
    }
}

int kruskalMST(const std::vector<std::array<int, 3>>& edges, int n) {
    std::vector<int> parent(n + 1);
    std::iota(parent.begin(), parent.end(), 0);

    std::vector<int> rank(n + 1);

    int weight = 0;
    int lastWeight = 0;
    for (const auto& [w, u, v] : edges)
        if (find(parent, u) != find(parent, v)) {
            unite(parent, rank, u, v);
            weight += lastWeight = w;
        }

    return weight - lastWeight;
}

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    int n, m;
    std::cin >> n >> m;

    std::vector<std::array<int, 3>> edges(m);
    for (int i = 0; i < m; ++i)
        std::cin >> edges[i][1] >> edges[i][2] >> edges[i][0];

    std::sort(edges.begin(), edges.end());

    std::cout << kruskalMST(edges, n) << '\n';
}
