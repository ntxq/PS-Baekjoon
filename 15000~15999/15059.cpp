#include <algorithm>
#include <iostream>
#include <limits>
#include <vector>

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    std::vector<int> stocks(3);
    std::cin >> stocks[0] >> stocks[1] >> stocks[2];

    std::vector<int> requests(3);
    std::cin >> requests[0] >> requests[1] >> requests[2];

    int unavailable = 0;
    for (int i = 0; i < 3; ++i)
        unavailable += std::max(0, requests[i] - stocks[i]);

    std::cout << unavailable << '\n';

    return 0;
}
