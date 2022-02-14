#include <algorithm>
#include <iostream>
#include <utility>

typedef long double ld;
typedef std::pair<ld, ld> vec;

ld crossProduct(const vec& a, const vec& b) {
    return a.first * b.second - a.second * b.first;
}

ld dotProduct(const vec& a, const vec& b) {
    return a.first * b.first + a.second * b.second;
}

vec operator+(const vec& a, const vec& b) {
    return vec(a.first + b.first, a.second + b.second);
}

vec operator-(const vec& a, const vec& b) {
    return vec(a.first - b.first, a.second - b.second);
}

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    ld x1, y1, x2, y2;
    ld x3, y3, x4, y4;
    std::cin >> x1 >> y1 >> x2 >> y2 >> x3 >> y3 >> x4 >> y4;

    vec p{x1, y1};
    vec r{x2 - x1, y2 - y1};
    vec q{x3, y3};
    vec s{x4 - x3, y4 - y3};

    ld cp = crossProduct(r, s);
    ld t = crossProduct(q - p, s) / cp;
    ld u = crossProduct(q - p, r) / cp;

    bool isIntersect = false;
    if (cp == 0 && crossProduct(q - p, r) == 0) {
        ld t0 = dotProduct(q - p, r) / dotProduct(r, r);
        ld t1 = t0 + dotProduct(s, r) / dotProduct(r, r);

        const ld& min = std::min(t0, t1);
        const ld& max = std::max(t0, t1);

        if (0 <= min && min <= 1)
            isIntersect = true;
        else if (0 <= max && max <= 1)
            isIntersect = true;
        else if (min < 0 && max > 1)
            isIntersect = true;
    } else if (cp != 0 && 0 <= t && t <= 1 && 0 <= u && u <= 1) {
        isIntersect = true;
    }

    std::cout << isIntersect << '\n';

    return 0;
}