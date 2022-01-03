#include <iostream>

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    int a, b, v;
    std::cin >> a >> b >> v;

    int days = (v - a) / (a - b);
    if ((v - a) % (a - b)) ++days;

    std::cout << days + 1;

    return 0;
}