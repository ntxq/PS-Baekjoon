#include <iostream>

unsigned long long pow(unsigned long long x, unsigned long long n) {
    if (n == 0)
        return 1;
    else if (n == 1)
        return x % 1000000007;
    else if (n % 2)
        return (x * pow((x * x) % 1000000007, n / 2)) % 1000000007;
    else
        return pow((x * x) % 1000000007, n / 2) % 1000000007;
}

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    int m;
    std::cin >> m;

    unsigned long long sum = 0;
    for (int i = 0; i < m; ++i) {
        unsigned long long ni, si;
        std::cin >> ni >> si;

        if (si % ni) {
            unsigned long long exp =
                (si * pow(ni, 1000000007 - 2)) % 1000000007;
            sum = (sum + exp) % 1000000007;
        } else {
            unsigned long long exp = si / ni;
            sum = (sum + exp) % 1000000007;
        }
    }

    std::cout << sum;

    return 0;
}