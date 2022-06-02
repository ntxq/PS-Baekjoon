#include <algorithm>
#include <iostream>

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    int numbers[3];
    for (int i = 0; i < 3; ++i) std::cin >> numbers[i];
    std::sort(numbers, numbers + 3);
    std::cout << numbers[1];

    return 0;
}