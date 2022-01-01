#include <iostream>

int main() {
    int cases;
    std::cin >> cases;

    for (int i = 0; i < cases; ++i) {
        int h, w, n;
        std::cin >> h >> w >> n;

        int y = (n - 1) % h + 1;
        int x = (n - 1) / h + 1;

        std::cout << y << (x < 10 ? "0" : "") << x << '\n';
    }

    return 0;
}