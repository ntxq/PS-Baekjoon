#include <algorithm>
#include <cmath>
#include <iostream>
#include <numeric>

double dist(int sx, int sy, int tx, int ty) {
    return std::sqrt((sx - tx) * (sx - tx) + (sy - ty) * (sy - ty));
}

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    int sx, sy;
    std::cin >> sx >> sy;

    int tx, ty, dx, dy;
    std::cin >> tx >> ty >> dx >> dy;

    dx = std::abs(dx);
    dy = std::abs(dy);
    int gcd = std::max(1, std::gcd(dx, dy));
    dx /= gcd;
    dy /= gcd;

    double minDist = dist(sx, sy, tx, ty);

    for (double nextDist = dist(sx, sy, tx + dx, ty + dy); nextDist < minDist;
         nextDist = dist(sx, sy, tx + dx, ty + dy)) {
        tx += dx;
        ty += dy;
        minDist = nextDist;
    }

    std::cout << tx << ' ' << ty << '\n';

    return 0;
}
