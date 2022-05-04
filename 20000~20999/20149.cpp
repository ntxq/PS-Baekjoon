#include <algorithm>
#include <iomanip>
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

bool operator==(const Point& a, const Point& b) {
    return a.x == b.x && a.y == b.y;
}

bool operator<=(const Point& a, const Point& b) {
    return (a.x < b.x) || (a.x == b.x && a.y <= b.y);
}

void find_intersection(const Point& p1, const Point& p2, const Point& p3,
                       const Point& p4) {
    double px = (p1.x * p2.y - p1.y * p2.x) * (p3.x - p4.x) -
                (p1.x - p2.x) * (p3.x * p4.y - p3.y * p4.x);
    double py = (p1.x * p2.y - p1.y * p2.x) * (p3.y - p4.y) -
                (p1.y - p2.y) * (p3.x * p4.y - p3.y * p4.x);
    double p = (p1.x - p2.x) * (p3.y - p4.y) - (p1.y - p2.y) * (p3.x - p4.x);

    if (p == 0) {
        if (p2 == p3 && p1 <= p3)
            std::cout << p2.x << ' ' << p2.y << '\n';
        else if (p1 == p4 && p3 <= p1)
            std::cout << p1.x << ' ' << p1.y << '\n';
    } else {
        double x = px / p;
        double y = py / p;

        std::cout << std::fixed << std::setprecision(9) << x << ' ' << y << '\n';
    }
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

void segmentsIntersect(Point p1, Point p2, Point p3,
                       Point p4) {
    long long d1 = direction(p3, p4, p1);
    long long d2 = direction(p3, p4, p2);
    long long d3 = direction(p1, p2, p3);
    long long d4 = direction(p1, p2, p4);

    if (d1 * d2 == 0 && d3 * d4 == 0) {
        if (p2 <= p1) std::swap(p1, p2);
        if (p4 <= p3) std::swap(p3, p4);

        if (p1 <= p4 && p3 <= p2) {
            std::cout << 1 << '\n';
            find_intersection(p1, p2, p3, p4);
            return;
        }
    } else if (d1 * d2 <= 0 && d3 * d4 <= 0) {
        std::cout << 1 << '\n';
        find_intersection(p1, p2, p3, p4);
        return;
    }

    std::cout << 0 << '\n';
}

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    Point p0, p1, p2, p3;
    std::cin >> p0.x >> p0.y >> p1.x >> p1.y >> p2.x >> p2.y >> p3.x >> p3.y;
    segmentsIntersect(p0, p1, p2, p3);

    return 0;
}