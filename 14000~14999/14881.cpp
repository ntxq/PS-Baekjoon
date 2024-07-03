#include <algorithm>
#include <iostream>
#include <limits>
#include <numeric>
#include <queue>
#include <vector>

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    int T;
    std::cin >> T;

    while (T--) {
        int a, b, c;
        std::cin >> a >> b >> c;

        bool is_possible = ((a >= c) || (b >= c)) && (c % std::gcd(a, b) == 0);
        std::cout << (is_possible ? "YES" : "NO") << '\n';
    }

    return 0;
}
