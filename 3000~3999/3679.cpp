#include <algorithm>
#include <iostream>
#include <limits>
#include <numeric>
#include <vector>

struct Point {
    int idx;
    int x;
    int y;

    bool operator==(const Point& other) const {
        return x == other.x && y == other.y;
    }

    bool operator<(const Point& other) const {
        return x < other.x || (x == other.x && y < other.y);
    }
};

int orientation(const Point& a, const Point& b, const Point& c) {
    int v = a.x * (b.y - c.y) + b.x * (c.y - a.y) + c.x * (a.y - b.y);
    if (v < 0) return -1;  // clockwise
    if (v > 0) return +1;  // counter-clockwise
    return 0;              // collinear
}

int dist(const Point& a, const Point& b) {
    int dx = a.x - b.x;
    int dy = a.y - b.y;
    return dx * dx + dy * dy;
}

void convex_hull(std::vector<Point>& points) {
    Point p0 = *std::min_element(points.begin(), points.end());

    std::sort(points.begin(), points.end(),
              [&p0](const Point& a, const Point& b) {
                  int o = orientation(p0, a, b);
                  if (o == 0)
                      return dist(p0, a) < dist(p0, b);
                  else
                      return o < 0;
              });

    int pt = points.size() - 1;
    while (pt > 1 && orientation(p0, points[pt], points[pt - 1]) == 0) --pt;

    std::reverse(points.begin() + pt, points.end());
    for (const Point& p : points) std::cout << p.idx << ' ';
    std::cout << '\n';
}

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    int T;
    std::cin >> T;

    while (T--) {
        int N;
        std::cin >> N;

        std::vector<Point> points(N);
        for (int i = 0; i < N; ++i) {
            points[i].idx = i;
            std::cin >> points[i].x >> points[i].y;
        }

        convex_hull(points);
    }

    return 0;
}
