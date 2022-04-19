#include <algorithm>
#include <iostream>
#include <vector>

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    unsigned long long N, M;
    std::cin >> N >> M;

    std::vector<unsigned long long> A(N);
    for (unsigned long long& a : A) std::cin >> a;

    std::vector<unsigned long long> prefix(M);

    unsigned long long count = 0;
    unsigned long long sum = 0;
    for (unsigned long long i = 0; i < N; ++i) {
        sum = (sum + A[i]) % M;
        if (sum == 0) ++count;

        count += prefix[sum];
        ++prefix[sum];
    }

    std::cout << count << '\n';

    return 0;
}
