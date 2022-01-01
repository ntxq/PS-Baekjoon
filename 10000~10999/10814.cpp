#include <algorithm>
#include <iostream>
#include <string>
#include <utility>
#include <vector>

int main() {
    int size;
    std::cin >> size;

    std::vector<std::pair<int, std::string>> v;
    for (int i = 0; i < size; ++i) {
        int a;
        std::string b;
        std::cin >> a >> b;
        v.push_back({a, b});
    }

    std::stable_sort(v.begin(), v.end(), [](const auto& a, const auto& b) {
        return a.first < b.first;
    });

    for (const auto& p : v) std::cout << p.first << ' ' << p.second << '\n';

    return 0;
}