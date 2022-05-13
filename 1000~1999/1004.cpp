#include <algorithm>
#include <cmath>
#include <iostream>

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    int T;
    std::cin >> T;

    while (T--) {
        int sx, sy, tx, ty;
        std::cin >> sx >> sy >> tx >> ty;

        int N;
        std::cin >> N;

        int crossCount = 0;
        for (int i = 0; i < N; ++i) {
            int cx, cy, r;
            std::cin >> cx >> cy >> r;

            bool isIncStart = (std::hypot(sx - cx, sy - cy) <= r);
            bool isIncEnd = (std::hypot(tx - cx, ty - cy) <= r);

            if (isIncStart != isIncEnd)
                ++crossCount;
        }

        std::cout << crossCount << '\n';
    }

    return 0;
}