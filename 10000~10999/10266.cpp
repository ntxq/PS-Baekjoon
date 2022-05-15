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

    const int SIZE = 360000;

    int N;
    std::cin >> N;

    std::string s(SIZE, '0');
    for (int i = 0; i < N; ++i) {
        int x;
        std::cin >> x;

        s[x] = '1';
    }

    std::string t(SIZE, '0');
    for (int i = 0; i < N; ++i) {
        int x;
        std::cin >> x;

        t[x] = '1';
    }

    auto pi = prefixFunction(s);

    bool isPossible = false;
    int curMatch = s[0] == t[0];
    for (int i = 1; i < SIZE && !isPossible; ++i) {
        while (curMatch && s[curMatch] != t[i]) curMatch = pi[curMatch - 1];
        if (s[curMatch] == t[i]) ++curMatch;
        if (curMatch == SIZE) isPossible = true;
    }
    for (int i = 0; i < SIZE && !isPossible; ++i) {
        while (curMatch && s[curMatch] != t[i]) curMatch = pi[curMatch - 1];
        if (s[curMatch] == t[i]) ++curMatch;
        if (curMatch == SIZE) isPossible = true;
    }

    std::cout << (isPossible ? "possible" : "impossible") << '\n';

    return 0;
}