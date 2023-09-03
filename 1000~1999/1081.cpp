#include <algorithm>
#include <array>
#include <iostream>

void calc(long long n, std::array<long long, 10>& counts, long long radix) {
    while (n) {
        counts[n % 10] += radix;
        n /= 10;
    }
}

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    long long start;
    long long end;
    std::cin >> start >> end;

    std::array<long long, 10> counts{};

    long long radix = 1;
    while (start <= end) {
        while (start % 10 && start <= end) calc(start++, counts, radix);
        while (end % 10 != 9 && start <= end) calc(end--, counts, radix);

        if (end < start) break;

        start /= 10;
        end /= 10;

        for (int i = 0; i < 10; ++i) counts[i] += (end - start + 1) * radix;

        radix *= 10;
    }

    long long sum = 0;
    for (int i = 0; i < 10; ++i) sum += i * counts[i];
    std::cout << sum << '\n';

    return 0;
}
