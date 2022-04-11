#include <algorithm>
#include <iostream>

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    std::vector<int> primes;
    std::vector<bool> sieve(10001, true);
    sieve[0] = sieve[1] = false;
    for (int i = 2; i <= 10000; ++i)
        if (sieve[i]) {
            primes.push_back(i);
            for (int j = i * i; j <= 10000; j += i) sieve[j] = false;
        }

    int T;
    std::cin >> T;

    for (int i = 0; i < T; ++i) {
        int n;
        std::cin >> n;

        auto min = primes.begin();
        auto max = std::lower_bound(primes.begin(), primes.end(), n);
        if (max == primes.end()) max = primes.end() - 1;
        auto dist = std::distance(min, max);

        auto curMin = min;
        auto curMax = max;
        int sum = *curMin + *curMax;

        while (curMin <= curMax) {
            if (sum == n && std::distance(curMin, curMax) < dist) {
                dist = std::distance(curMin, curMax);
                min = curMin;
                max = curMax;
            } else if (sum < n) {
                ++curMin;
                sum = *curMin + *curMax;
            } else {
                --curMax;
                sum = *curMin + *curMax;
            }
        }

        std::cout << *min << ' ' << *max << '\n';
    }

    return 0;
}
