#include <algorithm>
#include <cmath>
#include <iostream>

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    int W, H, X, Y, P;
    std::cin >> W >> H >> X >> Y >> P;

    int count = 0;
    for (int i = 0; i < P; ++i) {
        int x, y;
        std::cin >> x >> y;

        if (X <= x && x <= X + W && Y <= y && y <= Y + H)
            ++count;
        else if (std::hypot(x - X, y - Y - H / 2.0) <= H / 2.0)
            ++count;
        else if (std::hypot(x - X - W, y - Y - H / 2.0) <= H / 2.0)
            ++count;
    }

    std::cout << count << '\n';

    return 0;
}