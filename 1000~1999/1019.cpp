#include <algorithm>
#include <array>
#include <iostream>

void calc(unsigned long long n, std::array<unsigned long long, 10>& counts,
          unsigned long long radix) {
    while (n) {
        counts[n % 10] += radix;
        n /= 10;
    }
}

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    unsigned long long start = 1;
    unsigned long long end;
    std::cin >> end;

    std::array<unsigned long long, 10> counts{};

    unsigned long long radix = 1;
    while (start <= end) {
        while (start % 10 && start <= end) calc(start++, counts, radix);
        while (end % 10 != 9 && start <= end) calc(end--, counts, radix);

        if (end < start) break;

        start /= 10;
        end /= 10;

        for (int i = 0; i < 10; ++i) counts[i] += (end - start + 1) * radix;    

        radix *= 10;
    }

    for (int i : counts) std::cout << i << ' ';

    return 0;
}
