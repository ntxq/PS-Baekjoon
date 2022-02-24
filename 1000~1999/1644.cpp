#include <algorithm>
#include <iostream>
#include <numeric>
#include <vector>

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    int n;
    std::cin >> n;

    std::vector<bool> isPrime(n + 1, true);
    isPrime[0] = isPrime[1] = false;
    for (int i = 2; i <= n; ++i)
        if (isPrime[i])
            for (int j = i * 2; j <= n; j += i) isPrime[j] = false;

    std::vector<int> primes;
    for (int i = 2; i <= n; ++i)
        if (isPrime[i]) primes.push_back(i);

    int cnt = 0;
    int sum = 2;
    unsigned lo = 0, hi = 1;
    while (hi <= primes.size()) {
        if (sum == n) {
            ++cnt;
            sum -= primes[lo++];
        } else if (sum < n)
            sum += primes[hi++];
        else
            sum -= primes[lo++];
    }

    std::cout << cnt << '\n';

    return 0;
}
