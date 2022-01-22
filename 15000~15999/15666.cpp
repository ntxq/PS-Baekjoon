#include <algorithm>
#include <iostream>
#include <vector>

void backtrack(std::vector<int>& s, const std::vector<int>& bag, int level,
               int index) {
    if (!level) {
        for (const int& i : s) std::cout << i << ' ';
        std::cout << '\n';
        return;
    }

    for (unsigned i = index; i < bag.size(); ++i) {
        s.push_back(bag[i]);
        backtrack(s, bag, level - 1, i);
        s.pop_back();
    }
}

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    int n, m;
    std::cin >> n >> m;

    std::vector<int> bag;
    for (int i = 0; i < n; ++i) {
        int x;
        std::cin >> x;

        bag.push_back(x);
    }
    std::sort(bag.begin(), bag.end());
    bag.erase(std::unique(bag.begin(), bag.end()), bag.end());

    std::vector<int> s;
    backtrack(s, bag, m, 0);

    return 0;
}