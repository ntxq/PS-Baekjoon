#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    int N;
    std::cin >> N;

    std::vector<int> A(N);
    for (auto& x : A) std::cin >> x;

    std::vector<long long> prev(21);
    std::vector<long long> next(21);

    prev[A[0]] = 1;
    for (int i = 1; i < N - 1; ++i) {
        for (int j = 0; j < 21; ++j) {
            if (j + A[i] < 21) next[j + A[i]] += prev[j];
            if (j - A[i] >= 0) next[j - A[i]] += prev[j];
        }
        std::swap(prev, next);
        std::fill(next.begin(), next.end(), 0);
    }

    std::cout << prev[A[N - 1]] << '\n';

    return 0;
}
