#include <algorithm>
#include <iostream>
#include <limits>
#include <numeric>
#include <vector>

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    int sides[3];
    std::cin >> sides[0] >> sides[1] >> sides[2];

    std::sort(sides, sides + 3);
    sides[2] = std::min(sides[2], sides[0] + sides[1] - 1);

    std::cout << std::accumulate(sides, sides + 3, 0) << '\n';

    return 0;
}
