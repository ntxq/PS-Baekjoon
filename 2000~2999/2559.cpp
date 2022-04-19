#include <algorithm>
#include <iostream>
#include <vector>

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    int N, K;
    std::cin >> N >> K;

    std::vector<int> A(N);
    for (int& i : A) std::cin >> i;

    int maxSum = 0;
    int curSum = 0;
    for (int i = 0; i < K; ++i) curSum += A[i];
    maxSum = curSum;

    for (int i = K; i < N; ++i) {
        curSum += A[i];
        curSum -= A[i - K];
        if (curSum > maxSum) maxSum = curSum;
    }

    std::cout << maxSum << '\n';

    return 0;
}
