#include <algorithm>
#include <cmath>
#include <iostream>
#include <numeric>
#include <tuple>
#include <vector>

struct Point {
    double x;
    double y;
};

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

double kruskalMST(const std::vector<std::tuple<double, int, int>>& edges) {
    std::vector<int> parents(edges.size());
    std::iota(parents.begin(), parents.end(), 0);

    std::vector<int> ranks(edges.size());

    double sum = 0;
    for (const auto& [w, u, v] : edges)
        if (find(parents, u) != find(parents, v)) {
            unite(parents, ranks, u, v);
            sum += w;
        }

    return sum;
}

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    int n;
    std::cin >> n;

    std::vector<Point> stars(n);
    for (auto& star : stars) std::cin >> star.x >> star.y;

    std::vector<std::tuple<double, int, int>> edges;
    for (int i = 0; i < n; ++i)
        for (int j = i + 1; j < n; ++j) {
            double dx = stars[i].x - stars[j].x;
            double dy = stars[i].y - stars[j].y;
            double dist = std::sqrt(dx * dx + dy * dy);

            edges.emplace_back(dist, i, j);
            edges.emplace_back(dist, j, i);
        }

    std::sort(edges.begin(), edges.end());
    std::cout << kruskalMST(edges) << '\n';

    return 0;
}
