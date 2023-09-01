#include <algorithm>
#include <iostream>

int main() {
    std::cin.tie(0);
    std::ios_base::sync_with_stdio(false);

    long long a, b, c, d, u;
    std::cin >> a >> b >> c >> d >> u;

    long long cnt = 0;
    if (a <= u) ++cnt;
    cnt += std::max(0LL, (u - a) / b);

    if (long long fst = c; (fst < a || (fst - a) % b != 0) && fst <= u) ++cnt;

    for (long long i = c * d; i <= u && d > 1; i *= d)
        if (i < a || (i - a) % b != 0) ++cnt;

    std::cout << cnt << '\n';

    return 0;
}