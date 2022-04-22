#include <algorithm>
#include <iostream>
#include <vector>

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    long long N, k;
    std::cin >> N >> k;

    long long start = 1;
    long long end = k;
    long long res = 0;

    while (start <= end) {
        long long mid = (start + end) / 2;

        long long cnt = 0;
        for (long long i = 1; i <= N; ++i) cnt += std::min(mid / i, N);

        if (cnt >= k) {
            res = mid;
            end = mid - 1;
        } else {
            start = mid + 1;
        }
    }

    std::cout << res << '\n';

    return 0;
}