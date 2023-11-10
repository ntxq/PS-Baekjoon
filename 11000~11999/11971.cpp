#include <algorithm>
#include <iostream>
#include <limits>
#include <string>
#include <vector>

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    int N, M;
    std::cin >> N >> M;

    std::vector<int> speed_limits;
    for (int i = 0; i < N; ++i) {
        int l, v;
        std::cin >> l >> v;

        for (int j = 0; j < l; ++j) speed_limits.push_back(v);
    }

    std::vector<int> is_speeding;
    for (int i = 0; i < M; ++i) {
        int l, v;
        std::cin >> l >> v;

        for (int j = 0; j < l; ++j)
            is_speeding.push_back(v - speed_limits[is_speeding.size()]);
    }

    std::cout << std::max(0, *std::max_element(is_speeding.begin(),
                                               is_speeding.end()))
              << '\n';

    return 0;
}
