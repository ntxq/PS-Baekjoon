#include <algorithm>
#include <iostream>

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    int n;
    std::cin >> n;

    std::vector<int> a(n);
    for (int& i : a) std::cin >> i;

    int maxSum = a[0];
    int curSum = a[0];
    for (int i = 1; i < n; ++i) {
        curSum = std::max(curSum + a[i], a[i]);
        maxSum = std::max(maxSum, curSum);
    }

    std::cout << maxSum << '\n';

    return 0;
}
