#include <algorithm>
#include <array>
#include <iostream>
#include <string>

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    int N;
    std::cin >> N;

    int count = 0;
    for (int i = 0; i < N; ++i) {
        std::string s;
        std::cin >> s;

        std::array<bool, 26> group{};
        group[s[0] - 'a'] = true;

        bool isGroup = true;
        for (unsigned j = 1; j < s.size() && isGroup; ++j)
            if (s[j] != s[j - 1]) {
                isGroup = !group[s[j] - 'a'];
                group[s[j] - 'a'] = true;
            }

        count += isGroup;
    }

    std::cout << count << '\n';

    return 0;
}
