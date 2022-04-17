#include <algorithm>
#include <iostream>

int gcd(int a, int b) {
    if (!b) return a;
    return gcd(b, a % b);
}

int lcm(int a, int b) {
    return a * b / gcd(a, b);
}

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    int T;
    std::cin >> T;

    for (int i = 0; i < T; ++i) {
        int a, b;
        std::cin >> a >> b;

        std::cout << lcm(a, b) << '\n';
    }

    return 0;
}
