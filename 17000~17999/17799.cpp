#include <algorithm>
#include <iostream>
#include <limits>
#include <numeric>
#include <queue>
#include <vector>

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    int N, C;
    std::cin >> N >> C;

    std::vector<int> buckets(N);
    for (int& bucket : buckets) std::cin >> bucket;
    std::sort(buckets.begin(), buckets.end());

    int count = 0;

    int left = 0;
    int right = N - 1;
    while (left <= right) {
        if (buckets[left] + buckets[right] <= C) {
            ++left;
            --right;
        } else {
            --right;
        }
        ++count;
    }

    std::cout << count << '\n';

    return 0;
}
