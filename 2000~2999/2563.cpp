#include <algorithm>
#include <iostream>
#include <numeric>
#include <vector>

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    int C;
    std::cin >> C;

    std::vector<std::vector<bool>> papers(101, std::vector<bool>(101, false));
    for (int i = 0; i < C; ++i) {
        int left, bottom;
        std::cin >> left >> bottom;

        for (int j = left; j < left + 10; ++j)
            for (int k = bottom; k < bottom + 10; ++k) papers[j][k] = true;
    }

    std::cout << std::accumulate(papers.begin(), papers.end(), 0,
                                 [](int acc, const std::vector<bool>& v) {
                                     return acc + std::count(v.begin(), v.end(),
                                                             true);
                                 })
              << '\n';

    return 0;
}