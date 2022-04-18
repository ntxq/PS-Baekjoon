#include <algorithm>
#include <iostream>

unsigned long long gcd(unsigned long long a, unsigned long long b) {
    if (!b) return a;
    return gcd(b, a % b);
}

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    int N;
    std::cin >> N;

    int prev;
    int cur;

    unsigned long long numerator = 1;
    unsigned long long denominator = 1;

    std::cin >> prev;
    for (int i = 0; i < N - 1; ++i) {
        std::cin >> cur;

        numerator *= prev;
        denominator *= cur;

        unsigned long long g = gcd(numerator, denominator);
        numerator /= g;
        denominator /= g;

        std::cout << numerator << '/' << denominator << '\n';

        prev = cur;
    }

    return 0;
}
