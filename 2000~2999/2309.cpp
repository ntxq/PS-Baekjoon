#include <algorithm>
#include <iostream>
#include <numeric>

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    int heights[9];
    for (int i = 0; i < 9; ++i) std::cin >> heights[i];
    std::sort(std::begin(heights), std::end(heights));

    unsigned choices[9] = {0, 0, 1, 1, 1, 1, 1, 1, 1};
    int sum = std::accumulate(std::begin(heights) + 2, std::end(heights), 0);

    while (sum != 100) {
        std::next_permutation(std::begin(choices), std::end(choices));
        sum = 0;
        for (int i = 0; i < 9; ++i)
            if (choices[i]) sum += heights[i];
    }

    for (int i = 0; i < 9; ++i)
        if (choices[i]) std::cout << heights[i] << '\n';

    return 0;
}