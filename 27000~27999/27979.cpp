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

    std::vector<int> weights(N);
    for (int& w : weights) std::cin >> w;

    int cnt = 0;
    std::vector<bool> is_moved(N, false);
    for (int i = N - 1; i >= 0; --i) {
        if (is_moved[i]) continue;

        bool should_move = false;
        for (int j = i - 1; j >= 0 && !should_move; --j)
            if (weights[j] > weights[i]) should_move = true;

        if (!should_move) continue;

        ++cnt;
        is_moved[i] = true;

        for (int j = i - 1; j >= 0; --j)
            if (!is_moved[j] && weights[j] < weights[i]) {
                ++cnt;
                is_moved[j] = true;
            }
    }

    std::cout << cnt << '\n';

    return 0;
}
