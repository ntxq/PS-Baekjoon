#include <algorithm>
#include <iostream>
#include <vector>

void backtrack(std::vector<int>& s, const std::vector<int>& bag, int level,
               std::vector<int>& count) {
    if (!level) {
        for (const int& i : s) std::cout << i << ' ';
        std::cout << '\n';
        return;
    }

    for (unsigned i = 0; i < bag.size(); ++i) {
        if (count[bag[i]]) {
            s.push_back(bag[i]);
            --count[bag[i]];
            backtrack(s, bag, level - 1, count);
            ++count[bag[i]];
            s.pop_back();
        }
    }
}

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    int n, m;
    std::cin >> n >> m;

    std::vector<int> bag;
    std::vector<int> count(10001);
    for (int i = 0; i < n; ++i) {
        int x;
        std::cin >> x;

        if (!count[x]) bag.push_back(x);
        ++count[x];
    }
    std::sort(bag.begin(), bag.end());

    std::vector<int> s;
    backtrack(s, bag, m, count);

    return 0;
}