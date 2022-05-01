#include <algorithm>
#include <cmath>
#include <functional>
#include <iomanip>
#include <iostream>
#include <numeric>
#include <tuple>
#include <utility>
#include <vector>

typedef std::pair<int, int> Point;
typedef std::tuple<double, int, int> Edge;

int Find(int x, std::vector<int>& parents) {
    int root = parents[x];
    while (root != parents[root]) root = parents[root];
    while (root != parents[x]) {
        int next = parents[x];
        parents[x] = root;
        x = next;
    }
    return root;
}

void Union(int x, int y, std::vector<int>& parents, std::vector<int>& ranks) {
    int xroot = Find(x, parents);
    int yroot = Find(y, parents);

    if (xroot != yroot) {
        if (ranks[xroot] < ranks[yroot]) {
            parents[xroot] = yroot;
        } else if (ranks[xroot] > ranks[yroot]) {
            parents[yroot] = xroot;
        } else {
            parents[yroot] = xroot;
            ranks[xroot]++;
        }
    }
}

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    int N, M;
    std::cin >> N >> M;

    std::vector<int> parents(N + 1);
    std::vector<Point> points(N + 1);
    std::vector<int> ranks(N + 1);
    std::iota(parents.begin(), parents.end(), 0);

    int count = 0;

    for (int i = 1; i <= N; ++i)
        std::cin >> points[i].first >> points[i].second;

    for (int i = 0; i < M; ++i) {
        int x, y;
        std::cin >> x >> y;
        if (Find(x, parents) != Find(y, parents)) {
            Union(x, y, parents, ranks);
            ++count;
        }
    }

    std::vector<Edge> edges;
    for (int i = 1; i <= N; ++i) {
        for (int j = i + 1; j <= N; ++j) {
            edges.push_back({std::hypot(points[i].first - points[j].first,
                                        points[i].second - points[j].second),
                             i, j});
        }
    }
    std::sort(edges.begin(), edges.end(), std::greater<Edge>());

    double sumDist = 0;
    while (count != N - 1) {
        auto [w, x, y] = edges.back();
        edges.pop_back();

        if (Find(x, parents) != Find(y, parents)) {
            sumDist += w;
            Union(x, y, parents, ranks);
            ++count;
        }
    }

    std::cout << std::fixed << std::setprecision(2) << sumDist << '\n';

    return 0;
}