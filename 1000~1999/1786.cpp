#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

std::vector<int> prefixFunction(const std::string& s) {
    std::vector<int> pi(s.size());
    for (unsigned i = 1; i < s.size(); ++i) {
        int j = pi[i - 1];
        while (j && s[i] != s[j]) j = pi[j - 1];
        if (s[i] == s[j]) ++j;
        pi[i] = j;
    }

    return pi;
}

void kmpMatcher(const std::string& t, const std::string& p) {
    std::vector<int> pi = prefixFunction(p + '#' + t);

    std::cout << std::count(pi.begin(), pi.end(), p.size()) << '\n';
    for (auto it = std::find(pi.begin(), pi.end(), p.size()); it != pi.end();
         it = std::find(it + 1, pi.end(), p.size()))
        std::cout << (it - pi.begin() - 2 * p.size() + 1) << ' ';
}

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    std::string t, p;
    std::getline(std::cin, t);
    std::getline(std::cin, p);

    kmpMatcher(t, p);

    return 0;
}
