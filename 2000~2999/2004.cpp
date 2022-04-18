#include <algorithm>
#include <cmath>
#include <iostream>

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    unsigned long long n, m;
    std::cin >> n >> m;

    unsigned long long num5 = 0;
    unsigned long long denA5 = 0;
    unsigned long long denB5 = 0;

    for (unsigned long long i = 5; i <= n; i *= 5)
        num5 += n / i;

    for (unsigned long long i = 5; i <= m; i *= 5)
        denA5 += m / i;
    
    for (unsigned long long i = 5; i <= n - m; i *= 5)
        denB5 += (n - m) / i;

    unsigned long long num2 = 0;
    unsigned long long denA2 = 0;
    unsigned long long denB2 = 0;

    for (unsigned long long i = 2; i <= n; i *= 2)
        num2 += n / i;

    for (unsigned long long i = 2; i <= m; i *= 2)
        denA2 += m / i;
    
    for (unsigned long long i = 2; i <= n - m; i *= 2)
        denB2 += (n - m) / i;

    std::cout << std::min(num2 - denA2 - denB2, num5 - denA5 - denB5) << '\n';

    return 0;
}
