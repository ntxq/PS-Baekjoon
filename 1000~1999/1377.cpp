
#include <algorithm>
#include <iostream>
#include <limits>
#include <numeric>
#include <vector>

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    int N;
    std::cin >> N;

    std::vector<std::pair<int, int>> nums(N);
    for (int i = 0; i < N; ++i) {
        std::cin >> nums[i].first;
        nums[i].second = i;
    }

    std::sort(nums.begin(), nums.end());

    int ans = 0;
    for (int i = 0; i < N; ++i) ans = std::max(ans, nums[i].second - i + 1);
    std::cout << ans << '\n';

    return 0;
}
