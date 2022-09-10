#include <iostream>

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    unsigned long long a, b, c;
    std::cin >> a >> b >> c;
    std::cout << (a + b + c) << '\n';

    return 0;
}