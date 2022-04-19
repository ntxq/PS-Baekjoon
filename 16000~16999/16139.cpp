#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    std::string s;
    std::cin >> s;

    std::vector<std::vector<int>> dp(26, std::vector<int>(s.size()));
    for (int i = 0; i < 26; ++i) dp[i][0] = s[0] == 'a' + i;

    for (unsigned i = 1; i < s.size(); ++i)
        for (int j = 0; j < 26; ++j)
            if (s[i] == ('a' + j))
                dp[j][i] = dp[j][i - 1] + 1;
            else
                dp[j][i] = dp[j][i - 1];

    int q;
    std::cin >> q;

    for (int i = 0; i < q; ++i) {
        char a;
        int l, r;
        std::cin >> a >> l >> r;

        if (l)
            std::cout << dp[a - 'a'][r] - dp[a - 'a'][l - 1] << '\n';
        else
            std::cout << dp[a - 'a'][r] << '\n';
    }

    return 0;
}
