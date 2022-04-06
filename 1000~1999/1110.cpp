#include <algorithm>
#include <iostream>

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    int n;
    std::cin >> n;

    int cur = n;
    int count = 0;
    do {
        ++count;
        cur = (cur % 10) * 10 + (cur / 10 + cur % 10) % 10;
    } while (cur != n);

    std::cout << count << '\n';

    return 0;
}
