#include <algorithm>
#include <iostream>
#include <limits>
#include <numeric>
#include <vector>

void findDwarves(const std::vector<int>& hats) {
    int sum = std::accumulate(hats.begin(), hats.end(), 0);

    for (int i = 0; i < 9; ++i)
        for (int j = i + 1; j < 9; ++j)
            if (sum - hats[i] - hats[j] == 100) {
                for (int k = 0; k < 9; ++k)
                    if (k != i && k != j) std::cout << hats[k] << '\n';
                return;
            }

    return;
}

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    std::vector<int> hats(9);
    for (int& hat : hats) std::cin >> hat;

    findDwarves(hats);

    return 0;
}
