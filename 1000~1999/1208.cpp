#include <algorithm>
#include <iostream>
#include <map>
#include <vector>

void subsequenceSum(const std::vector<int>& A,
                    std::map<int, unsigned long long>& dp, unsigned i, int j) {
    if (i == A.size() / 2) {
        ++dp[j];
        return;
    }

    subsequenceSum(A, dp, i + 1, j);
    subsequenceSum(A, dp, i + 1, j + A[i]);
}

unsigned long long subsequenceSumToS(const std::vector<int>& A,
                                     std::map<int, unsigned long long>& dp,
                                     unsigned i, int j, int s) {
    if (i == A.size()) return dp[s - j];

    return subsequenceSumToS(A, dp, i + 1, j, s) +
           subsequenceSumToS(A, dp, i + 1, j + A[i], s);
}

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    int N, S;
    std::cin >> N >> S;

    std::vector<int> A(N);
    for (int& i : A) std::cin >> i;

    std::map<int, unsigned long long> dp;
    subsequenceSum(A, dp, 0, 0);

    auto ans = subsequenceSumToS(A, dp, A.size() / 2, 0, S);
    if (S == 0) --ans;

    std::cout << ans << '\n';

    return 0;
}