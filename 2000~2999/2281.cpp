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

    std::vector<int> names(N);
    for (auto& name : names) std::cin >> name;

    std::vector<int> prev(M + 1, std::numeric_limits<int>::max());
    std::vector<int> curr(M + 1, std::numeric_limits<int>::max());
    prev[names[0]] = 0;

    for (int i = 0; i < N - 1; ++i) {
        for (int j = 0; j <= M; ++j)
            if (prev[j] != std::numeric_limits<int>::max()) {
                if (j + names[i + 1] < M)
                    curr[j + names[i + 1] + 1] =
                        std::min(curr[j + names[i + 1] + 1], prev[j]);

                const int cost = (M - j) * (M - j);
                curr[names[i + 1]] =
                    std::min(curr[names[i + 1]], prev[j] + cost);
            }
        std::swap(prev, curr);
        std::fill(curr.begin(), curr.end(), std::numeric_limits<int>::max());
    }

    std::cout << *std::min_element(prev.begin(), prev.end()) << '\n';

    return 0;
}
