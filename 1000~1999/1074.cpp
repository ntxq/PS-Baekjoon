#include <iostream>

unsigned countZ(unsigned n, unsigned r, unsigned c) {
    if (n == 1) return 2 * r + c;

    unsigned pow = 1 << ((n - 1) * 2);
    unsigned size = 1 << (n - 1);
    if (r < size) {
        if (c < size)
            return countZ(n - 1, r, c);
        else
            return pow + countZ(n - 1, r, c - size);
    } else {
        if (c < size)
            return pow * 2 + countZ(n - 1, r - size, c);
        else
            return pow * 3 + countZ(n - 1, r - size, c - size);
    }
}

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    unsigned n, r, c;
    std::cin >> n >> r >> c;
    std::cout << countZ(n, r, c);

    return 0;
}