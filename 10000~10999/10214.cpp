#include <algorithm>
#include <iostream>
#include <limits>
#include <vector>

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    int T;
    std::cin >> T;

    while (T--) {
        int y = 0;
        int k = 0;

        for (int i = 0; i < 9; ++i) {
            int a, b;
            std::cin >> a >> b;

            y += a;
            k += b;
        }

        if (y > k)
            std::cout << "Yonsei\n";
        else if (y < k)
            std::cout << "Korea\n";
        else
            std::cout << "Draw\n";
    }

    return 0;
}
