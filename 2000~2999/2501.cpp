#include <algorithm>
#include <iostream>
#include <limits>
#include <numeric>
#include <set>
#include <vector>

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    int N;
    unsigned K;
    std::cin >> N >> K;

    std::set<int> divisors;
    for (int i = 1; i * i <= N; ++i)
        if (N % i == 0) {
            divisors.insert(i);
            divisors.insert(N / i);
        }

    if (divisors.size() < K)
        std::cout << 0 << '\n';
    else
        std::cout << *std::next(divisors.begin(), K - 1) << '\n';

    return 0;
}
