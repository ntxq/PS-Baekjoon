#include <algorithm>
#include <cmath>
#include <iostream>
#include <numbers>
#include <utility>
#include <vector>

struct Point {
    double x;
    double y;
};

Point getCartesian(int r, int order) {
    double theta = std::numbers::pi / 4 * order;
    return {r * std::cos(theta), r * std::sin(theta)};
}

bool ccw(Point a, Point b, Point c) {
    double v = a.x * (b.y - c.y) + b.x * (c.y - a.y) + c.x * (a.y - b.y);
    return v > 0;
}

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    std::vector<int> scores(8);
    for (int& i : scores) std::cin >> i;
    std::sort(scores.begin(), scores.end());

    int count = 0;
    for (int i = 0; i < 40320;
         ++i, std::next_permutation(scores.begin(), scores.end())) {
        std::vector<Point> points;
        for (int j = 0; j < 8; ++j)
            points.push_back(getCartesian(scores[j], j));

        bool isConvex = true;
        for (int j = 0; j < 8; ++j)
            if (!ccw(points[j], points[(j + 1) % 8], points[(j + 2) % 8])) {
                isConvex = false;
                break;
            }

        if (isConvex) ++count;
    }

    std::cout << count << '\n';

    return 0;
}