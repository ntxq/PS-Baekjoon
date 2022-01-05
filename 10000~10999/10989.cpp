#include <iostream>

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    int n;
    std::cin >> n;

    int* numbers = new int[10000]{};
    for (int i = 0, num; i < n; ++i) {
        std::cin >> num;
        ++numbers[num - 1];
    }

    for (int i = 0; i < 10000; ++i)
        for (int j = 0; j < numbers[i]; ++j) std::cout << i + 1 << '\n';

    return 0;
}