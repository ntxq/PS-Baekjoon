#include <algorithm>
#include <iostream>

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    int a, b;
    std::cin >> a >> b;

    std::cout << (a * (b % 10)) << '\n'
              << (a * (b / 10 % 10)) << '\n'
              << (a * (b / 100)) << '\n'
              << (a * b) << '\n';

    return 0;
}
