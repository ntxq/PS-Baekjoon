#include <algorithm>
#include <iostream>
#include <numeric>
#include <tuple>
#include <vector>

int find(std::vector<int>& parents, int x) {
    int root = x;
    while (parents[root] != root) root = parents[root];

    while (parents[x] != root) {
        int next = parents[x];
        parents[x] = root;
        x = next;
    }

    return root;
}

void unite(std::vector<int>& parents, std::vector<int>& ranks, int x, int y) {
    int xroot = find(parents, x);
    int yroot = find(parents, y);

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

int kruskalMST(const std::vector<std::tuple<int, int, int>>& edges, int n) {
    std::vector<int> parents(n);
    std::vector<int> ranks(n);
    std::iota(parents.begin(), parents.end(), 0);

    int sum = 0;
    for (const auto& [d, x, y] : edges) {
        if (find(parents, x) != find(parents, y)) {
            unite(parents, ranks, x, y);
            sum += d;
        }
    }

    return sum;
}

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    int n;
    std::cin >> n;

    std::vector<std::pair<int, int>> X;
    std::vector<std::pair<int, int>> Y;
    std::vector<std::pair<int, int>> Z;
    for (int i = 0; i < n; ++i) {
        int x, y, z;
        std::cin >> x >> y >> z;

        X.emplace_back(x, i);
        Y.emplace_back(y, i);
        Z.emplace_back(z, i);
    }

    std::sort(X.begin(), X.end());
    std::sort(Y.begin(), Y.end());
    std::sort(Z.begin(), Z.end());

    std::vector<std::tuple<int, int, int>> edges;
    for (int i = 0; i < n - 1; ++i) {
        edges.emplace_back(X[i + 1].first - X[i].first, X[i].second,
                           X[i + 1].second);
        edges.emplace_back(Y[i + 1].first - Y[i].first, Y[i].second,
                           Y[i + 1].second);
        edges.emplace_back(Z[i + 1].first - Z[i].first, Z[i].second,
                           Z[i + 1].second);
    }    

    std::sort(edges.begin(), edges.end());

    std::cout << kruskalMST(edges, n) << '\n';

    return 0;
}
