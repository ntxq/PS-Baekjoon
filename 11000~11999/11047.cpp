#include <algorithm>
#include <iostream>
#include <vector>

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    int n, k;
    std::cin >> n >> k;

    std::vector<int> coins(n);
    for (int& coin : coins) std::cin >> coin;

    int count = 0;
    for (int i = n - 1; i >= 0 && k; --i) {
        count += k / coins[i];
        k %= coins[i];
    }

    std::cout << count;

    return 0;
}