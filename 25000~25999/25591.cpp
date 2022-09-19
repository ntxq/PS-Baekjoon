#include <iostream>

int main()
{
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    int x, y;
    std::cin >> x >> y;

    int a = 100 - x;
    int b = 100 - y;
    int c = 100 - a - b;
    int d = a * b;
    int q = d / 100;
    int r = d % 100;

    std::cout << a << ' ' << b << ' ' << c << ' ' << d << ' ' << q << ' ' << r << '\n'
              << (c + q) << ' ' << r << '\n';

    return 0;
}