#include <algorithm>
#include <iostream>
#include <limits>
#include <numeric>
#include <string>
#include <vector>

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    int N;
    std::cin >> N;

    std::vector<std::pair<std::string, std::string>> names(N);
    for (int i = 0; i < N; ++i) std::cin >> names[i].first >> names[i].second;

    std::sort(names.begin(), names.end(), [](const auto& a, const auto& b) {
        return (a.first == b.first) ? a.second > b.second : a.first < b.first;
    });

    for (const auto& [first, second] : names)
        std::cout << first << ' ' << second << '\n';

    return 0;
}
