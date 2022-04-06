#include <algorithm>
#include <iostream>

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    int t;
    std::cin >> t;

    for (int i = 0; i < t; ++i) {
        int a, b;
        std::cin >> a >> b;

        std::cout << "Case #" << i + 1 << ": " << a + b << '\n';
    }

    return 0;
}
