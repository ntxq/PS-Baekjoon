#include <iostream>

int inca(int m, int n, int x, int y) {
    y %= n;

    for (int i = x; i <= m * n; i += m)
        if (i % n == y) return i;

    return -1;
}

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    int t;
    std::cin >> t;

    for (int i = 0; i < t; ++i) {
        int m, n, x, y;
        std::cin >> m >> n >> x >> y;

        std::cout << inca(m, n, x, y) << '\n';
    }

    return 0;
}