#include <algorithm>
#include <iostream>
#include <vector>

void dfs(unsigned idx, long long sum, std::vector<long long>& bag,
         const std::vector<int>& candidates) {
    if (idx == candidates.size()) {
        bag.push_back(sum);
        return;
    }

    dfs(idx + 1, sum, bag, candidates);
    dfs(idx + 1, sum + candidates[idx], bag, candidates);
}

long long dfsCount(unsigned idx, long long sum, long long C,
                   const std::vector<long long>& bag,
                   const std::vector<int>& candidates) {
    if (idx == candidates.size())
        return std::upper_bound(bag.begin(), bag.end(), C - sum) - bag.begin();

    return dfsCount(idx + 1, sum, C, bag, candidates) +
           dfsCount(idx + 1, sum + candidates[idx], C, bag, candidates);
}

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    long long N, C;
    std::cin >> N >> C;

    std::vector<int> candidate1;
    for (int i = 0; i < N / 2; ++i) {
        int x;
        std::cin >> x;
        candidate1.push_back(x);
    }

    std::vector<int> candidate2;
    for (int i = 0; i < N - N / 2; ++i) {
        int x;
        std::cin >> x;
        candidate2.push_back(x);
    }

    std::vector<long long> bag;
    dfs(0, 0, bag, candidate1);
    std::sort(bag.begin(), bag.end());

    std::cout << dfsCount(0, 0, C, bag, candidate2) << '\n';

    return 0;
}