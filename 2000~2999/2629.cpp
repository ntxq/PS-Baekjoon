#include <algorithm>
#include <iostream>
#include <limits>
#include <queue>
#include <tuple>
#include <vector>

typedef std::tuple<int, int, int, int> Node;

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    int W;
    std::cin >> W;

    std::vector<int> weights(W);
    for (int& i : weights) std::cin >> i;

    std::vector<bool> isValid(40001);
    isValid[0] = true;
    for (int weight : weights)
        for (int j = 40000; j >= weight; --j)
            isValid[j] = isValid[j] || isValid[j - weight];

    for (int weight : weights)
        for (int j = 0; j <= 40000 - weight; ++j)
            isValid[j] = isValid[j] || isValid[j + weight];

    int T;
    std::cin >> T;

    for (int i = 0; i < T; ++i) {
        int weight;
        std::cin >> weight;

        std::cout << (isValid[weight] ? 'Y' : 'N') << ' ';
    }

    return 0;
}