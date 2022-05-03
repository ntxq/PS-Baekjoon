#include <algorithm>
#include <iostream>
#include <vector>

struct Point {
    long long x;
    long long y;
};

Point operator-(const Point& a, const Point& b) {
    return {a.x - b.x, a.y - b.y};
}

long long operator*(const Point& a, const Point& b) {
    return a.x * b.y - a.y * b.x;
}

long long direction(const Point& i, const Point& j, const Point& k) {
    long long ccw = (k - i) * (j - i);
    if (ccw > 0)
        return 1;
    else if (ccw < 0)
        return -1;
    else
        return 0;
}

bool onSegment(const Point& i, const Point& j, const Point& k) {
    if (std::min(i.x, j.x) <= k.x && k.x <= std::max(i.x, j.x) &&
        std::min(i.y, j.y) <= k.y && k.y <= std::max(i.y, j.y))
        return true;
    return false;
}

bool segmentsIntersect(const Point& p1, const Point& p2, const Point& p3,
                       const Point& p4) {
    long long d1 = direction(p3, p4, p1);
    long long d2 = direction(p3, p4, p2);
    long long d3 = direction(p1, p2, p3);
    long long d4 = direction(p1, p2, p4);

    if (d1 * d2 <= 0 && d3 * d4 <= 0) return true;
    return false;
}

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    Point p0, p1, p2, p3;
    std::cin >> p0.x >> p0.y >> p1.x >> p1.y >> p2.x >> p2.y >> p3.x >> p3.y;

    std::cout << segmentsIntersect(p0, p1, p2, p3) << '\n';

    return 0;
}