#include <algorithm>
#include <iostream>
#include <vector>

struct Point {
    int x;
    int y;
};

Point operator-(const Point& a, const Point& b) {
    return {a.x - b.x, a.y - b.y};
}

int operator*(const Point& a, const Point& b) { return a.x * b.y - a.y * b.x; }

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    Point p0, p1, p2;
    std::cin >> p0.x >> p0.y >> p1.x >> p1.y >> p2.x >> p2.y;

    int ccw = (p1 - p0) * (p2 - p0);
    std::cout << (ccw == 0 ? 0 : (ccw > 0 ? 1 : -1)) << '\n';

    return 0;
}