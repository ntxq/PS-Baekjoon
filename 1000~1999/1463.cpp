#include <algorithm>
#include <iostream>

int countOne(int x) {
    if (x <= 1) return 0;
    int div2 = countOne(x / 2) + x % 2 + 1;
    int div3 = countOne(x / 3) + x % 3 + 1;
    return std::min(div2, div3);
}

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    int x;
    std::cin >> x;

    std::cout << countOne(x);

    return 0;
}