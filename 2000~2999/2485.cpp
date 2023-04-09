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

    std::vector<int> trees(N);
    for (int& pos : trees) std::cin >> pos;

    std::vector<int> dists(N);
    std::adjacent_difference(trees.begin(), trees.end(), dists.begin());

    int gcd = std::accumulate(dists.begin() + 1, dists.end(), dists[1],
                              [](int a, int b) { return std::gcd(a, b); });

    int cnt = 0;
    for (int i = 1; i < N; ++i) cnt += (dists[i] / gcd) - 1;

    std::cout << cnt << '\n';

    return 0;
}
