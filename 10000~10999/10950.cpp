#include <iostream>

int main() {
    int size;
    std::cin >> size;

    for (int i = 0; i < size; ++i) {
        int x, y;
        std::cin >> x >> y;
        std::cout << x + y << '\n';
    }

    return 0;
}