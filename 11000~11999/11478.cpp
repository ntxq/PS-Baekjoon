#include <algorithm>
#include <iostream>
#include <set>
#include <string>

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    std::string S;
    std::cin >> S;

    std::set<std::string> words;

    for (unsigned i = 0; i < S.size(); ++i)
        for (unsigned j = i + 1; j <= S.size(); ++j)
            words.insert(S.substr(i, j - i));

    std::cout << words.size() << '\n';

    return 0;
}