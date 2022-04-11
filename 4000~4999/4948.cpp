#include <algorithm>
#include <iostream>

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    std::vector<int> cases;
    int t;
    int max;
    while (std::cin >> t && t) {
        cases.push_back(t);
        max = std::max(max, t);
    }

    std::vector<bool> sieve(2 * max + 1, true);
    sieve[0] = sieve[1] = false;
    for (int i = 2; i * i <= 2 * max; ++i)
        if (sieve[i])
            for (int j = i * i; j <= 2 * max; j += i) sieve[j] = false;

    for (int i : cases) {
        int count = 0;
        for (int j = i + 1; j <= 2 * i; ++j)
            if (sieve[j]) ++count;

        std::cout << count << '\n';
    }

    return 0;
}
