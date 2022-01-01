#include <iostream>

int main() {
    int size;
    std::cin >> size;

    int min = 1000000;
    int max = -1000000;

    while (size--) {
        int num;
        std::cin >> num;

        if (num > max) max = num;
        if (num < min) min = num;
    }

    std::cout << min << ' ' << max;

    return 0;
}