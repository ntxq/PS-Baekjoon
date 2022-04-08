#include <algorithm>
#include <iomanip>
#include <iostream>
#include <numeric>
#include <vector>

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    int C;
    std::cin >> C;

    while (C--) {
        int N;
        std::cin >> N;

        std::vector<int> scores(N);
        for (int& i : scores) std::cin >> i;

        double mean = std::reduce(scores.begin(), scores.end(), 0.0) / N;
        int count = std::count_if(scores.begin(), scores.end(),
                                  [mean](int i) { return i > mean; });
        std::cout << std::fixed << std::setprecision(3) << 100.0 * count / N
                  << "%\n";
    }

    return 0;
}
