#include <algorithm>
#include <iostream>

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    int n;
    std::cin >> n;

    int f1 = 0, f2 = 1;
    for (int i = 0; i < n; ++i) {
        int f3 = f1 + f2;
        f1 = f2;
        f2 = f3;
    }

    std::cout << f1 << '\n';

    return 0;
}
