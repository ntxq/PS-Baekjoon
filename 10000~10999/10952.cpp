#include <iostream>

int main() {
    int x, y;

    while (std::cin >> x >> y)
        if (x || y) std::cout << x + y << '\n';

    return 0;
}