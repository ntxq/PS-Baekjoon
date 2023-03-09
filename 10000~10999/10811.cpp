#include <algorithm>
#include <iostream>
#include <limits>
#include <numeric>
#include <vector>

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    int N, M;
    std::cin >> N >> M;

    std::vector<int> baskets(N);
    std::iota(baskets.begin(), baskets.end(), 1);

    for (int i = 0; i < M; ++i) {
        int a, b;
        std::cin >> a >> b;

        std::reverse(baskets.begin() + a - 1, baskets.begin() + b);
    }

    for (int x : baskets)
        std::cout << x << ' ';
    std::cout << '\n';

    return 0;
}
