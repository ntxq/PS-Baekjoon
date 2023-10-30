#include <algorithm>
#include <iostream>
#include <limits>
#include <string>
#include <vector>

void count_transform(int cnt, std::string s) {
    if (s.length() <= 1) {
        std::cout << cnt << '\n';

        int x = std::stoi(s);
        std::cout << (x % 3 == 0 ? "YES" : "NO") << '\n';

        return;
    }

    int x = 0;
    for (char c : s) x += c - '0';

    count_transform(cnt + 1, std::to_string(x));
}

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    std::string s;
    std::cin >> s;

    count_transform(0, s);

    return 0;
}
