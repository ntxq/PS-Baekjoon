#include <algorithm>
#include <iostream>
#include <vector>

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    int N;
    std::cin >> N;

    std::vector<int> A(N);
    for (int& i : A) std::cin >> i;

    std::vector<int> LIS;
    std::vector<int> P(N);

    for (int i = 0; i < N; ++i) {
        auto it = std::lower_bound(LIS.begin(), LIS.end(), i,
                                   [&A](int a, int b) { return A[a] < A[b]; });
        if (it == LIS.end()) {
            P[i] = (LIS.empty() ? -1 : LIS.back());
            LIS.push_back(i);
        } else {
            P[i] = (it == LIS.begin() ? -1 : *(it - 1));
            *it = i;
        }
    }

    std::cout << LIS.size() << '\n';

    std::vector<int> LIS_seq;
    for (int i = LIS.back(); i != -1; i = P[i]) 
        LIS_seq.push_back(A[i]);
    for (auto it = LIS_seq.rbegin(); it != LIS_seq.rend(); ++it)
        std::cout << *it << ' ';

    return 0;
}