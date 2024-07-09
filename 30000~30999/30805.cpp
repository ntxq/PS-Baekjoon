#include <algorithm>
#include <iostream>
#include <limits>
#include <numeric>
#include <vector>

int find_max_common(const std::vector<int>& aCounts,
                    const std::vector<int>& bCounts) {
    for (int i = 100; i >= 0; --i)
        if (aCounts[i] > 0 && bCounts[i] > 0) return i;

    return 0;
}

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    int N;
    std::cin >> N;

    std::vector<int> A(N);
    for (int& a : A) std::cin >> a;

    int M;
    std::cin >> M;

    std::vector<int> B(M);
    for (int& b : B) std::cin >> b;

    std::vector<int> aCounts(101);
    for (int a : A) ++aCounts[a];

    std::vector<int> bCounts(101);
    for (int b : B) ++bCounts[b];

    int x = 0;
    int y = 0;
    std::vector<int> seq;

    int maxNum = find_max_common(aCounts, bCounts);
    while (maxNum) {
        while (x < N && A[x] != maxNum) --aCounts[A[x++]];
        while (y < M && B[y] != maxNum) --bCounts[B[y++]];

        seq.push_back(maxNum);
        --aCounts[A[x++]];
        --bCounts[B[y++]];

        maxNum = find_max_common(aCounts, bCounts);
    }

    std::cout << seq.size() << '\n';
    for (int num : seq) std::cout << num << ' ';
    std::cout << '\n';

    return 0;
}
