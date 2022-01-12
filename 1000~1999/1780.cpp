#include <algorithm>
#include <array>
#include <iostream>
#include <vector>

template <unsigned long N>
std::array<int, N> operator+(const std::array<int, N>& a,
                             const std::array<int, N>& b) {
    std::array<int, N> result;
    std::transform(a.begin(), a.end(), b.begin(), result.begin(),
                   std::plus<int>());
    return result;
}

template <unsigned long long N>
std::array<int, N> operator+(const std::array<int, N>& a,
                             const std::array<int, N>& b) {
    std::array<int, N> result;
    std::transform(a.begin(), a.end(), b.begin(), result.begin(),
                   std::plus<int>());
    return result;
}

std::array<int, 3> cutPaper(int x, int y, int dim,
                            const std::vector<std::vector<int>>& paper) {
    if (std::all_of(paper.begin() + x, paper.begin() + x + dim,
                    [&](const std::vector<int>& row) {
                        return std::all_of(
                            row.begin() + y, row.begin() + y + dim,
                            [&](const int& val) { return val == paper[x][y]; });
                    }))
        return {paper[x][y] == -1, paper[x][y] == 0, paper[x][y] == 1};

    return cutPaper(x, y, dim / 3, paper) +
           cutPaper(x + dim / 3, y, dim / 3, paper) +
           cutPaper(x + 2 * dim / 3, y, dim / 3, paper) +
           cutPaper(x, y + dim / 3, dim / 3, paper) +
           cutPaper(x + dim / 3, y + dim / 3, dim / 3, paper) +
           cutPaper(x + 2 * dim / 3, y + dim / 3, dim / 3, paper) +
           cutPaper(x, y + 2 * dim / 3, dim / 3, paper) +
           cutPaper(x + dim / 3, y + 2 * dim / 3, dim / 3, paper) +
           cutPaper(x + 2 * dim / 3, y + 2 * dim / 3, dim / 3, paper);
}

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    int n;
    std::cin >> n;

    std::vector<std::vector<int>> paper(n, std::vector<int>(n));
    for (auto& i : paper)
        for (auto& j : i) std::cin >> j;

    for (int i : cutPaper(0, 0, n, paper)) std::cout << i << '\n';

    return 0;
}