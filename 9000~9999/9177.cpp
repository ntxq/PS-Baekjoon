#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

bool solve(const std::string& a, const std::string& b, const std::string& c) {
    if (c.size() == 0) return true;

    if (a.back() == c.back() && b.back() == c.back())
        return solve(a.substr(0, a.size() - 1), b, c.substr(0, c.size() - 1)) ||
               solve(a, b.substr(0, b.size() - 1), c.substr(0, c.size() - 1));
    else if (a.back() == c.back())
        return solve(a.substr(0, a.size() - 1), b, c.substr(0, c.size() - 1));
    else if (b.back() == c.back())
        return solve(a, b.substr(0, b.size() - 1), c.substr(0, c.size() - 1));
    else
        return false;
}

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    int T;
    std::cin >> T;

    for (int i = 1; i <= T; ++i) {
        std::string a, b, c;
        std::cin >> a >> b >> c;

        std::cout << "Data set " << i << ": " << (solve(a, b, c) ? "yes" : "no") << '\n';
    }

    return 0;
}