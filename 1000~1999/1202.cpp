#include <algorithm>
#include <array>
#include <iostream>
#include <set>
#include <vector>

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    int n, k;
    std::cin >> n >> k;

    std::vector<std::array<int, 2>> jewellery(n);
    for (int i = 0; i < n; ++i) std::cin >> jewellery[i][0] >> jewellery[i][1];

    std::multiset<int> available;
    for (int i = 0; i < k; ++i) {
        int x;
        std::cin >> x;

        available.insert(x);
    }

    std::sort(jewellery.begin(), jewellery.end(),
              [](const auto& a, const auto& b) { return a[1] > b[1]; });

    unsigned long long sum = 0;
    for (int i = 0; i < n && !available.empty(); ++i) {
        auto bag = available.lower_bound(jewellery[i][0]);

        if (bag != available.end()) {
            sum += jewellery[i][1];
            available.erase(bag);
        }
    }

    std::cout << sum;

    return 0;
}