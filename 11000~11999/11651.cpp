#include <algorithm>
#include <iostream>
#include <utility>
#include <vector>

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    int n;
    std::cin >> n;

    std::vector<std::pair<int, int>> v(n);
    for (int i = 0; i < n; ++i) std::cin >> v[i].second >> v[i].first;

    std::sort(v.begin(), v.end());

    for (const auto& p : v) std::cout << p.second << ' ' << p.first << '\n';

    return 0;
}