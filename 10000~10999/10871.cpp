#include <iostream>

int main() {
    int size, threshold;
    std::cin >> size >> threshold;

    bool first = true;
    while (size--) {
        int num;
        std::cin >> num;

        if (num < threshold) {
            if (first) {
                std::cout << num;
                first = false;
            } else
                std::cout << ' ' << num;
        }
    }

    return 0;
}