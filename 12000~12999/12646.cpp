#include <algorithm>
#include <iostream>
#include <limits>
#include <numeric>
#include <string>
#include <vector>

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    int T;
    std::cin >> T;

    for (int i = 0; i < T; ++i) {
        std::string s;
        std::cin >> s;

        if (std::next_permutation(s.begin(), s.end())) {
            std::cout << "Case #" << i + 1 << ": " << s << '\n';
        } else {
            std::string nextS = "";
            int zeroCnt = 0;
            while (s[zeroCnt] == '0') ++zeroCnt;
            
            nextS += s[zeroCnt];
            nextS += std::string(zeroCnt + 1, '0');
            nextS += s.substr(zeroCnt + 1);

            std::cout << "Case #" << i + 1 << ": " << nextS << '\n';
        }
    }

    return 0;
}
