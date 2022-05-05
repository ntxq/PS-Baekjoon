#include <algorithm>
#include <cmath>
#include <iomanip>
#include <iostream>

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    int X, Y, D, T;
    std::cin >> X >> Y >> D >> T;

    double dist = std::hypot(X, Y);
    double ans = dist;

    int cnt = dist / D;
    dist -= cnt * D;

    ans = std::min({ans, (cnt + 1.0) * T + D - dist, (cnt + (cnt ? 1.0 : 2.0)) * T, cnt * T + dist});
    std::cout << std::fixed << std::setprecision(10) << ans << '\n';

    return 0;
}