#include <algorithm>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <numbers>

double findArea(double r1, double r2, double d) {
    double r1s = r1 * r1;
    double r2s = r2 * r2;
    double ds = d * d;

    if (r1 + r2 <= d) return 0;
    if (d + r1 <= r2 || d + r2 <= r1)
        return std::numbers::pi * std::min(r1s, r2s);

    return r1s * std::acos((ds + r1s - r2s) / (2 * d * r1)) +
           r2s * std::acos((ds + r2s - r1s) / (2 * d * r2)) -
           0.5 * std::sqrt((-d + r1 + r2) * (d + r1 - r2) * (d - r1 + r2) *
                           (d + r1 + r2));
}

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    double x1, y1, r1;
    double x2, y2, r2;

    std::cin >> x1 >> y1 >> r1;
    std::cin >> x2 >> y2 >> r2;

    double xd = x1 - x2;
    double yd = y1 - y2;

    double area = findArea(r1, r2, std::hypot(xd, yd));

    std::cout << std::fixed << std::setprecision(3) << area << '\n';

    return 0;
}