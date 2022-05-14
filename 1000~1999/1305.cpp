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

    int L;
    std::string S;
    std::cin >> L >> S;

    auto pi = prefixFunction(S);
    unsigned K = pi.size() - pi[pi.size() - 1];
    std::cout << K << '\n';

    return 0;
}