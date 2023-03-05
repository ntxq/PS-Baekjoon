#include <algorithm>
#include <cctype>
#include <iostream>
#include <limits>
#include <numeric>
#include <string>
#include <vector>

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    std::string s;
    std::getline(std::cin, s);

    std::string t;
    for (char c : s) {
        if (std::isalpha(c)) {
            char base = (std::isupper(c) ? 'A' : 'a');
            t += base + ((c - base + 13) % 26);
        } else {
            t += c;
        }
    }

    std::cout << t << '\n';

    return 0;
}
