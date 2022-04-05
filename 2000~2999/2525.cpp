#include <algorithm>
#include <iostream>

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    int h, m, t;
    std::cin >> h >> m >> t;

    m += t;
    if (m >= 60) {
        h += m / 60;
        m %= 60;
    }

    if (h >= 24) {
        h %= 24;
    }

    std::cout << h << " " << m;

    return 0;
}
