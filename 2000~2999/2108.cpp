#include <algorithm>
#include <cmath>
#include <iostream>
#include <numeric>
#include <vector>

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    int n;
    std::cin >> n;

    std::vector<int> v(n);
    std::vector<int> count(8001);

    for (int i = 0; i < n; ++i) {
        std::cin >> v[i];
        ++count[v[i] + 4000];
    }

    std::sort(v.begin(), v.end());

    int avg = std::round(std::accumulate(v.begin(), v.end(), 0) /
                         static_cast<double>(n));

    int median = v[n / 2];

    int mode;
    if (auto firstMax = std::max_element(count.cbegin(), count.cend()),
        secondMax = std::max_element(firstMax + 1, count.cend());
        *firstMax == *secondMax)
        mode = secondMax - count.cbegin() - 4000;
    else
        mode = firstMax - count.cbegin() - 4000;

    int range = v[n - 1] - v[0];

    std::cout << avg << '\n' << median << '\n' << mode << '\n' << range;

    return 0;
}