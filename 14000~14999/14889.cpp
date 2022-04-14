#include <algorithm>
#include <iostream>
#include <limits>
#include <vector>

void backtrack(unsigned x, int& minDiff, std::vector<int>& M,
               const std::vector<std::vector<int>>& S) {
    if (x == S.size()) {
        if (M.size() != S.size() / 2)
            return;

        std::vector<bool> others(S.size(), false);

        int s1 = 0;
        for (int i : M) {
            others[i] = true;
            for (int j : M) s1 += S[i][j];
        }

        std::vector<int> M2;
        for (unsigned i = 0; i < others.size(); ++i)
            if (!others[i]) M2.push_back(i);

        int s2 = 0;
        for (int i : M2)
            for (int j : M2) s2 += S[i][j];

        int diff = std::abs(s1 - s2);
        if (diff < minDiff) minDiff = diff;
        return;
    }

    backtrack(x + 1, minDiff, M, S);
    M.push_back(x);
    backtrack(x + 1, minDiff, M, S);
    M.pop_back();
}

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    int N;
    std::cin >> N;

    std::vector<std::vector<int>> S(N, std::vector<int>(N));
    for (auto& i : S)
        for (auto& j : i) std::cin >> j;

    int minDiff = std::numeric_limits<int>::max();
    std::vector<int> M;
    backtrack(0, minDiff, M, S);

    std::cout << minDiff << '\n';

    return 0;
}
