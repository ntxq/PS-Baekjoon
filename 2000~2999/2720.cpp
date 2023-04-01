#include <algorithm>
#include <iostream>
#include <limits>
#include <numeric>
#include <string>
#include <vector>

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    int t;
    std::cin >> t;

    int coins[4] = {25, 10, 5, 1};

    while (t--) {
        int c;
        std::cin >> c;

        for (int i = 0; i < 4; ++i) {
            int count = c / coins[i];
            std::cout << count << ' ';
            c %= coins[i];
        }
        std::cout << '\n';
    }

    return 0;
}
