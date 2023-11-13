#include <algorithm>
#include <iostream>
#include <limits>
#include <string>
#include <vector>

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    int N, M;
    std::cin >> N >> M;

    std::vector<int> wages(N);
    for (int& wage : wages) std::cin >> wage;

    long long maxSum = 0;
    for (int i = 0; i < M; ++i) maxSum += wages[i];

    long long curSum = maxSum;
    for (int i = M; i < N; ++i) {
        curSum += wages[i] - wages[i - M];
        maxSum = std::max(maxSum, curSum);
    }

    std::cout << maxSum << '\n';

    return 0;
}
