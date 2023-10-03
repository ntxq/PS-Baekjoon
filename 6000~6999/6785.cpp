#include <algorithm>
#include <iostream>
#include <limits>
#include <numeric>
#include <vector>

bool isCrystal(int m, int x, int y) {
    if (m == 0) return false;

    int base = 1;
    for (int i = 1; i < m; ++i) base *= 5;

    int cx = x / base;
    int cy = y / base;

    if (1 <= cx && cx <= 3 && cy == 0) return true;
    if (cx == 2 && cy == 1) return true;

    if (cx == 1 && cy == 1) return isCrystal(m - 1, x - base, y - base);
    if (cx == 3 && cy == 1) return isCrystal(m - 1, x - base * 3, y - base);
    if (cx == 2 && cy == 2) return isCrystal(m - 1, x - base * 2, y - base * 2);

    return false;
}

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    int T;
    std::cin >> T;

    while (T--) {
        int m, x, y;
        std::cin >> m >> x >> y;

        std::cout << (isCrystal(m, x, y) ? "crystal" : "empty") << '\n';
    }

    return 0;
}
