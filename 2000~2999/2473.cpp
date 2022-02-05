#include <algorithm>
#include <cmath>
#include <iostream>
#include <vector>

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    int n;
    std::cin >> n;

    std::vector<long long> liquids(n);
    for (auto& liquid : liquids) std::cin >> liquid;

    std::sort(liquids.begin(), liquids.end());

    int base = 0;
    int minLow = 1;
    int minHigh = n - 1;
    long long minSum =
        std::abs(liquids[base] + liquids[minLow] + liquids[minHigh]);

    for (int b = 0; b < n - 2; ++b) {
        int i = b + 1;
        int j = n - 1;
        while (i < j) {
            long long curSum = liquids[b] + liquids[i] + liquids[j];
            if (long long absSum = std::abs(curSum); absSum < minSum) {
                minSum = absSum;
                base = b;
                minLow = i;
                minHigh = j;
            }

            if (curSum < 0)
                ++i;
            else
                --j;
        }
    }

    std::cout << liquids[base] << ' ' << liquids[minLow] << ' '
              << liquids[minHigh] << '\n';

    return 0;
}