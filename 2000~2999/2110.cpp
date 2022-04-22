#include <algorithm>
#include <iostream>
#include <vector>

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    int N, C;
    std::cin >> N >> C;

    std::vector<int> houses(N);
    for (int& i : houses) std::cin >> i;
    std::sort(houses.begin(), houses.end());

    int start = 1;
    int end = houses.back() - houses.front();
    int result = 0;

    while (start <= end) {
        int mid = (start + end) / 2;

        int count = 1;
        int prev = houses.front();
        for (int i = 1; i < N; ++i)
            if (houses[i] - prev >= mid) {
                ++count;
                prev = houses[i];
            }

        if (count >= C) {
            result = std::max(result, mid);
            start = mid + 1;
        } else {
            end = mid - 1;
        }
    }

    std::cout << result << '\n';

    return 0;
}