#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

std::vector<int> prefixFunction(const std::string& s) {
    std::vector<int> pi(s.size());

    for (unsigned i = 1; i < pi.size(); ++i) {
        int j = pi[i - 1];
        while (j && s[i] != s[j]) j = pi[j - 1];
        if (s[i] == s[j]) ++j;
        pi[i] = j;
    }

    return pi;
}

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    std::string s;
    while (std::cin >> s && s != ".") {
        auto pi = prefixFunction(s);
        std::vector<int> ans(pi.size() + 1);

        unsigned k = pi.size() - pi[pi.size() - 1];
        if (pi.size() % k)
            std::cout << 1 << '\n';
        else
            std::cout << pi.size() / k << '\n';
    }

    return 0;
}