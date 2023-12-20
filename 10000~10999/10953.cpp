#include <algorithm>
#include <iostream>
#include <limits>
#include <string>
#include <vector>

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    int T;
    std::cin >> T;

    while (T--) {
        std::string s;
        std::cin >> s;

        std::cout << (s[0] - '0') + (s[2] - '0') << '\n';
    }

    return 0;
}
