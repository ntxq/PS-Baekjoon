#include <algorithm>
#include <iostream>

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    int a, b;
    std::cin >> a >> b;

    if (a < 0 && b < 0)
        std::cout << 3;
    else if (a < 0)
        std::cout << 2;
    else if (b < 0)
        std::cout << 4;
    else
        std::cout << 1;

    return 0;
}
