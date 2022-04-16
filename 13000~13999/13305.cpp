#include <algorithm>
#include <iostream>

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    int N;
    std::cin >> N;

    std::vector<int> edges(N - 1);
    for (int& i : edges) std::cin >> i;

    std::vector<int> prices(N);
    for (int& i : prices) std::cin >> i;

    int minPrice = prices[0];
    unsigned long long curDist = 0;
    unsigned long long curSum = 0;

    for (int i = 0; i < N - 1; ++i) {
        if (prices[i] < minPrice) {
            curSum += minPrice * curDist;
            minPrice = prices[i];
            curDist = 0;
        }
        curDist += edges[i];
    }
    curSum += minPrice * curDist;

    std::cout << curSum << '\n';

    return 0;
}
