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

        int cnt = 1;
        char prev = s[0];

        for (size_t i = 1; i < s.size(); ++i) {
            if (s[i] == prev) {
                ++cnt;
            } else {
                std::cout << cnt << prev;
                cnt = 1;
                prev = s[i];
            }
        }
        std::cout << cnt << prev << '\n';
    }

    return 0;
}
