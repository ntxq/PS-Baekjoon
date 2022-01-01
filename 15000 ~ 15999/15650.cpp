#include <iostream>
#include <numeric>
#include <vector>

void backtracking(const std::vector<int>& bag, std::vector<int>& seq,
                  unsigned start, unsigned length) {
    if (!length) {
        for (const int& i : seq) std::cout << i << ' ';
        std::cout << '\n';
        return;
    }

    for (unsigned i = start; i < bag.size(); ++i) {
        seq.push_back(bag[i]);
        backtracking(bag, seq, i + 1, length - 1);
        seq.pop_back();
    }

    return;
}

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    int n, m;
    std::cin >> n >> m;

    std::vector<int> a(n);
    std::iota(a.begin(), a.end(), 1);

    std::vector<int> b;
    backtracking(a, b, 0, m);

    return 0;
}