#include <iostream>

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    int x, y, w, h;
    std::cin >> x >> y >> w >> h;

    x = x > w - x ? w - x : x;
    y = y > h - y ? h - y : y;

    std::cout << (x > y ? y : x);

    return 0;
}