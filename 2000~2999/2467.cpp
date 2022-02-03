#include <algorithm>
#include <cmath>
#include <iostream>
#include <utility>
#include <vector>

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    int n;
    std::cin >> n;

    std::vector<int> solutions(n);
    for (int& i : solutions) std::cin >> i;

    std::sort(solutions.begin(), solutions.end());

    std::pair<int, int> best = {0, n - 1};
    int bestDiff = std::abs(solutions[best.first] + solutions[best.second]);

    int i = 0;
    int j = n - 1;
    while (i < j) {
        int diff = solutions[i] + solutions[j];
        if (int absDiff = std::abs(diff); absDiff < bestDiff) {
            best = {i, j};
            bestDiff = absDiff;
        }

        if (diff < 0)
            ++i;
        else
            --j;
    }

    std::cout << solutions[best.first] << ' ' << solutions[best.second];

    return 0;
}