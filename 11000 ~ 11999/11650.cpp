#include <algorithm>
#include <iostream>
#include <utility>
#include <vector>

int main() {
    int size;
    std::cin >> size;

    std::vector<std::pair<int, int>> v;
    for (int i = 0; i < size; ++i) {
        int a;
        int b;
        std::cin >> a >> b;
        v.push_back({a, b});
    }

    std::sort(v.begin(), v.end());

    for (const auto& [x, y] : v) std::cout << x << ' ' << y << '\n';

    return 0;
}