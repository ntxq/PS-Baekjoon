#include <algorithm>
#include <iostream>
#include <vector>

int possibleCables(const std::vector<unsigned long long>& cables,
                   unsigned long long cutLength) {
    int sum = 0;
    for (const unsigned long long& cable : cables) sum += cable / cutLength;

    return sum;
}

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    int k, n;
    std::cin >> k >> n;

    std::vector<unsigned long long> cables(k);
    for (int i = 0; i < k; ++i) std::cin >> cables[i];

    std::sort(cables.begin(), cables.end());

    unsigned long long minCutLength = 1;
    unsigned long long maxCutLength = cables[k - 1];
    unsigned long long cutLength = maxCutLength;

    while (minCutLength + 1 < maxCutLength) {
        int count = possibleCables(cables, cutLength);

        if (count < n)
            maxCutLength = cutLength;
        else
            minCutLength = cutLength;

        cutLength = (minCutLength + maxCutLength) / 2;
    }

    std::cout << cutLength;

    return 0;
}