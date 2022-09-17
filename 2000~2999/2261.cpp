#include <algorithm>
#include <iostream>
#include <limits>
#include <utility>
#include <vector>

using Point = std::pair<int, int>;

int dist(const Point& a, const Point& b) {
    const int dx = a.first - b.first;
    const int dy = a.second - b.second;
    return dx * dx + dy * dy;
}

int solve(const std::vector<Point>& points, int l, int r) {
    if (r - l <= 3) {
        int d = std::numeric_limits<int>::max();
        for (int i = l; i < r; ++i)
            for (int j = i + 1; j < r; ++j)
                d = std::min(d, dist(points[i], points[j]));

        return d;
    }

    int m = (l + r) / 2;
    int mx = points[m].first;
    int d = std::min(solve(points, l, m), solve(points, m, r));

    std::vector<Point> yPoints;
    for (int i = l; i < r; ++i)
        if (int dx = points[i].first - mx; dx * dx < d)
            yPoints.push_back(points[i]);

    std::sort(
        yPoints.begin(), yPoints.end(),
        [](const Point& a, const Point& b) { return a.second < b.second; });

    for (unsigned i = 0; i < yPoints.size(); ++i)
        for (unsigned j = i + 1; j < yPoints.size() && j - i < 8; ++j)
            d = std::min(d, dist(yPoints[i], yPoints[j]));

    return d;
}

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    int N;
    std::cin >> N;

    std::vector<Point> points(N);
    for (auto& [x, y] : points) std::cin >> x >> y;
    std::sort(points.begin(), points.end());

    std::cout << solve(points, 0, N) << '\n';

    return 0;
}