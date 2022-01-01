#include <algorithm>
#include <iostream>
#include <iterator>
#include <string>
#include <vector>

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    int n, m;
    std::cin >> n >> m;

    std::vector<std::string> a;
    for (int i = 0; i < n; ++i) {
        std::string s;
        std::cin >> s;
        a.push_back(s);
    }

    std::vector<std::string> b;
    for (int i = 0; i < m; ++i) {
        std::string s;
        std::cin >> s;
        b.push_back(s);
    }

    std::sort(a.begin(), a.end());
    std::sort(b.begin(), b.end());

    std::vector<std::string> c;
    std::set_intersection(a.begin(), a.end(), b.begin(), b.end(),
                          std::back_inserter(c));

    std::cout << c.size() << '\n';
    for (const auto& s : c) {
        std::cout << s << '\n';
    }

    return 0;
}