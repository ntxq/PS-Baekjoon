#include <algorithm>
#include <iostream>
#include <utility>
#include <vector>

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    int n, k;
    std::cin >> n >> k;

    std::vector<std::pair<int, int>> items(n);
    for (int i = 0; i < n; ++i) std::cin >> items[i].first >> items[i].second;

    std::vector<int> bag(k + 1);
    for (const auto& item : items)
        for (int i = 0; i < k + 1 - item.first; ++i)
            bag[i] = std::max(bag[i], bag[i + item.first] + item.second);

    std::cout << bag[0];

    return 0;
}