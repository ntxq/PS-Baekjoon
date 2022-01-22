#include <algorithm>
#include <array>
#include <iostream>
#include <vector>

void backtrack(std::vector<int>& s, int max, int level) {
    if (!level) {
        for (const int& i : s) std::cout << i << ' ';
        std::cout << '\n';
        return;
    }

    for (int i = s.empty() ? 1 : s.back(); i <= max; ++i) {
        s.push_back(i);
        backtrack(s, max, level - 1);
        s.pop_back();
    }
}

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    int n, m;
    std::cin >> n >> m;

    std::vector<int> s;
    backtrack(s, n, m);

    return 0;
}