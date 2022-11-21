#include <algorithm>
#include <iostream>
#include <numeric>
#include <vector>

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    int N;
    std::cin >> N;

    std::vector<int> seq(N);
    for (auto& i : seq) std::cin >> i;

    if (std::prev_permutation(seq.begin(), seq.end()))
        for (auto i : seq) std::cout << i << ' ';
    else
        std::cout << -1;
    std::cout << '\n';

    return 0;
}