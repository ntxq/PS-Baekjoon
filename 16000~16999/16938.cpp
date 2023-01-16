#include <algorithm>
#include <iostream>
#include <numeric>
#include <vector>

int N, L, R, X;
std::vector<long long> A;

int backtrack(int first, int idx, int last, long long sum) {
    if (idx == N) return (L <= sum && sum <= R && A[last] - A[first] >= X);

    int count = 0;
    if (first == -1)
        count += backtrack(idx, idx + 1, idx, A[idx]);
    else
        count += backtrack(first, idx + 1, idx, sum + A[idx]);

    count += backtrack(first, idx + 1, last, sum);

    return count;
}

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    std::cin >> N >> L >> R >> X;

    A.resize(N);
    for (auto& i : A) std::cin >> i;
    std::sort(A.begin(), A.end());

    std::cout << backtrack(-1, 0, -1, 0) << '\n';

    return 0;
}