#include <algorithm>
#include <iostream>
#include <numeric>
#include <utility>
#include <vector>

void backtracking(std::vector<int>& bag, std::vector<int>& seq,
                  unsigned length) {
    if (!length) {
        for (const int& i : seq) std::cout << i << ' ';
        std::cout << '\n';
        return;
    }

    int tmp = -1;
    for (unsigned i = 0; i < bag.size(); ++i) {
        if (bag[i] != -1) {
            std::swap(bag[i], tmp);
            seq.push_back(tmp);
            backtracking(bag, seq, length - 1);
            seq.pop_back();
            std::swap(bag[i], tmp);
        }
    }

    return;
}

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    int n, m;
    std::cin >> n >> m;

    std::vector<int> a(n);
    for (int& i : a) std::cin >> i;

    std::sort(a.begin(), a.end());

    std::vector<int> b;
    backtracking(a, b, m);

    return 0;
}