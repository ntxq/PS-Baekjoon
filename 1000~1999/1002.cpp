#include <algorithm>
#include <cmath>
#include <iostream>

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    int T;
    std::cin >> T;

    for (int i = 0; i < T; ++i) {
        int x1, y1, r1;
        int x2, y2, r2;
        std::cin >> x1 >> y1 >> r1 >> x2 >> y2 >> r2;

        if (x1 == x2 && y1 == y2) {
            if (r1 == r2)
                std::cout << -1 << '\n';
            else
                std::cout << 0 << '\n';

            continue;
        }

        double d = std::sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
        double l = (r1 * r1 - r2 * r2 + d * d) / (2 * d);
        if (r1 * r1 < l * l) {
            std::cout << 0 << '\n';
            continue;
        }
        double h = std::sqrt(r1 * r1 - l * l);

        if (h / d * (y2 - y1) == 0 && h / d * (x2 - x1) == 0)
            std::cout << 1 << '\n';
        else
            std::cout << 2 << '\n';
    }

    return 0;
}
