#include <algorithm>
#include <iostream>
#include <limits>
#include <numeric>
#include <vector>

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    int T;
    std::cin >> T;

    while (T--) {
        int p, m, f, c;
        std::cin >> p >> m >> f >> c;

        int chicken = m / p;
        int coupon = chicken * c;

        int x = chicken + coupon / f;
        int y = chicken + (coupon >= f ? (1 + (coupon - f) / (f - c)) : 0);

        std::cout << y - x << '\n';
    }

    return 0;
}
