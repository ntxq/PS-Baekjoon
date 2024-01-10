#include <algorithm>
#include <iostream>
#include <limits>
#include <numeric>
#include <string>
#include <vector>

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    std::string s, t;
    std::cin >> s >> t;

    std::vector<std::vector<int>> byChars(26);
    for (int i = 0; i < s.size(); ++i) byChars[s[i] - 'a'].push_back(i);

    long long count = 0;
    for (int i = 0; i < s.size(); ++i) {
        int idx = i;
        for (int j = 0; j < t.size() && idx <= s.size(); ++j) {
            int ch = t[j] - 'a';
            auto next =
                std::lower_bound(byChars[ch].begin(), byChars[ch].end(), idx);
            if (next == byChars[ch].end())
                idx = s.size() + 1;
            else
                idx = *next + 1;
        }

        if (idx <= s.size()) count += s.size() - idx + 1;
    }

    std::cout << count << '\n';

    return 0;
}
