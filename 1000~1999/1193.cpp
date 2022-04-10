#include <algorithm>
#include <iostream>

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    int X;
    std::cin >> X;

    int diag = 0;
    int offset = 0;
    for (int i = 1; i < X; i += diag + 1) {
        ++diag;
        offset = X - i - 1;
    }

    if (diag % 2)
        std::cout << offset + 1 << '/' << diag - offset + 1 << '\n';
    else
        std::cout << diag - offset + 1 << '/' << offset + 1 << '\n';

    return 0;
}
